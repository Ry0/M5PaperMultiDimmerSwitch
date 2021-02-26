#include <M5EPD.h>
#include "ImageResource.h"
#include "ui_manager.h"
#include "hap_manager.h"
#include "wifi_info.h"

M5EPD_Canvas canvas(&M5.EPD);
ui_manager UI(&canvas);
hap_manager HAP;

void setup()
{
    M5.begin();

    // define ui design
    // top left
    UI.create_button(50, 60, 190, 160, ImageResource_top_button_190x160, ImageResource_top_button_black_190x160);
    UI.create_object(50, 220, 190, 60, ImageResource_middle_button_190x60);
    UI.create_button(50, 280, 190, 160, ImageResource_bottom_button_190x160, ImageResource_bottom_button_black_190x160);

    // top right
    UI.create_button(300, 60, 190, 160, ImageResource_top_button_190x160, ImageResource_top_button_black_190x160);
    UI.create_object(300, 220, 190, 60, ImageResource_middle_button_190x60);
    UI.create_button(300, 280, 190, 160, ImageResource_bottom_button_190x160, ImageResource_bottom_button_black_190x160);

    // bottom left
    UI.create_button(50, 60 + 460, 190, 160, ImageResource_top_button_190x160, ImageResource_top_button_black_190x160);
    UI.create_object(50, 220 + 460, 190, 60, ImageResource_middle_button_190x60);
    UI.create_button(50, 280 + 460, 190, 160, ImageResource_bottom_button_190x160, ImageResource_bottom_button_black_190x160);

    // bottom right
    UI.create_button(300, 60 + 460, 190, 160, ImageResource_top_button_190x160, ImageResource_top_button_black_190x160);
    UI.create_object(300, 220 + 460, 190, 60, ImageResource_middle_button_190x60);
    UI.create_button(300, 280 + 460, 190, 160, ImageResource_bottom_button_190x160, ImageResource_bottom_button_black_190x160);

    // label (x, y, font_size, color, cache_size, title);
    UI.create_label(145, 242, 22, 15, 256, "シーリングライト");
    UI.create_label(395, 242, 22, 15, 256, "デスクライト");
    UI.create_label(145, 702, 22, 15, 256, "テレビ");
    UI.create_label(395, 702, 22, 15, 256, "エアコン");

    // Initialize after "create_xxxx"
    UI.initialize();

    // Draw the initial state of UI
    UI.draw_all(UPDATE_MODE_GC16);

    // Try to connect wifi.
    HAP.connect_wifi(ssid, password);

    // Associating GUI with HAP
    auto id_num = UI.get_button_num();
    HAP.initialize(id_num);
}

void loop()
{
    // Return 0 or more if the button is pressed, -1 otherwise.
    int id = UI.check_executable_button_id();
    if (id >= 0)
    {
        Serial.printf("execute button (id = %d)\n", id);
        HAP.button_callback(id, button_event_single_press);
        // When the process is finished, set the button to the default color.
        UI.release_button(id, UPDATE_MODE_DU);
    }
}
