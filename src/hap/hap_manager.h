#ifndef _HAP_MANAGER_H_
#define _HAP_MANAGER_H_

#include <FS.h>
#include <SPIFFS.h>
#include "../data_struct.h"

extern "C"
{
#include "homeintegration.h"
}

class hap_manager
{
public:
    hap_manager();
    void initialize(int button_num, bool reset = false);
    void button_callback(int button_id, button_event_t event);

private:
    void format_spiffs_();
    void init_hap_storage_(bool reset = false);
    static void storage_changed_(char *szstorage, int size);
    void notify_hap_(int button_id, uint8_t val);

    int button_num_ = 0;
    // std::vector<int> button_id_map_;
    // std::map<int, homekit_service_t> id_to_homekit_service_dic_;
    // std::vector<homekit_service_t> homekit_service_list_;
    homekit_service_t **homekit_service_;

    const String pair_file_name_ = "/pair.dat";
};

#endif
