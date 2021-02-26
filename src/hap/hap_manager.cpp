#include "hap_manager.h"
#include "../assembly_info.h"

hap_manager::hap_manager()
{
}

void hap_manager::connect_wifi(const char *ssid, const char *passphrase)
{
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, passphrase);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void hap_manager::initialize(int button_num, bool reset)
{
    init_hap_storage_(reset);
    set_callback_storage_change(storage_changed_);

    // We will use for this example only one accessory (possible to use a several on the same esp)
    // Our accessory type is programmable switch , apple interface will proper show that
    hap_setbase_accessorytype(homekit_accessory_category_programmable_switch);
    // init base properties
    hap_initbase_accessory_service(user_setting_model_name, user_setting_manufacturer, user_setting_serial_number, user_setting_models_type, user_setting_version);
    // hap_initbase_accessory_service("M5Paper Button", "Ry0_Ka", "0", "EspHapButton", "1.0");

    button_num_ = button_num;
    for (int id = 0; id < button_num; id++)
    {
        Serial.printf("registerd button start(Button Id: %d)\n", id);
        hap_add_button_service("Button");
        Serial.printf("registerd button end(Button Id: %d)\n", id);
    }
    //and finally init HAP
    hap_init_homekit_server();

    // Get all services.
    homekit_service_ = hap_get_server_config()->accessories[0]->services;
}

void hap_manager::format_spiffs_()
{
    Serial.println("Please wait 30 secs for SPIFFS to be formatted");
    SPIFFS.format();
    Serial.println("Spiffs formatted");
}

void hap_manager::init_hap_storage_(bool reset)
{

    Serial.print("init_hap_storage");
    if (!SPIFFS.begin(true))
    {
        Serial.print("SPIFFS Mount failed");
    }

    //If the HomeKit accessory is not recognized, please Format SPIFFS.
    if (reset == true)
    {
        format_spiffs_();
    }

    File fsDAT = SPIFFS.open("/pair.dat", "r");
    if (!fsDAT)
    {
        Serial.println("Failed to read pair.dat");
        return;
    }

    int size = hap_get_storage_size_ex();
    char *buf = new char[size];
    memset(buf, 0xff, size);
    int readed = fsDAT.readBytes(buf, size);
    Serial.print("Readed bytes ->");
    Serial.println(readed);
    hap_init_storage_ex(buf, size);
    fsDAT.close();
    delete[] buf;
}

void hap_manager::storage_changed_(char *szstorage, int size)
{
    SPIFFS.remove("/pair.dat");
    File fsDAT = SPIFFS.open("/pair.dat", "w+");
    if (!fsDAT)
    {
        Serial.println("Failed to open pair.dat");
        return;
    }
    fsDAT.write((uint8_t *)szstorage, size);

    fsDAT.close();
}

void hap_manager::button_callback(int button_id, button_event_t event)
{
    Serial.println("button_callback");
    switch (event)
    {
    case button_event_single_press:
        notify_hap_(button_id, 0);
        break;
    case button_event_double_press:
        notify_hap_(button_id, 1);
        break;
    case button_event_long_press:
        notify_hap_(button_id, 2);
        break;
    }
}

void hap_manager::notify_hap_(int button_id, uint8_t val)
{
    if (0 <= button_id && button_id < button_num_)
    {
        Serial.printf("button id = %d\n", button_id);
        Serial.println("notify hap");
        homekit_characteristic_t *ch = homekit_service_characteristic_by_type(homekit_service_[button_id + 1], HOMEKIT_CHARACTERISTIC_PROGRAMMABLE_SWITCH_EVENT);

        if (ch)
        {
            ch->value.int_value = val;
            homekit_characteristic_notify(ch, ch->value);
            Serial.println("notify hap is successed.");
        }
    }
}