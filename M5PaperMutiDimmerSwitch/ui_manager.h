#ifndef _UI_MANAGER_H_
#define _UI_MANAGER_H_

#include <M5EPD.h>
#include <Arduino.h>
#include <FS.h>
#include <vector>
#include "data_struct.h"
#include "id_generator.h"
#include "ui_object.h"
#include "ui_label.h"

class ui_manager
{
public:
    ui_manager(M5EPD_Canvas *canvas, String font_file_path);
    void initialize();
    void create_button(int x, int y, int w, int h, const uint8_t *default_image_data, const uint8_t *tapped_image_data);
    void create_object(int x, int y, int w, int h, const uint8_t *image_data);
    void create_label(int x, int y, uint8_t size, uint16_t color, uint16_t cache_size, String title);

    void draw_all(m5epd_update_mode_t mode);
    void push_button(int id, m5epd_update_mode_t mode);
    void release_button(int id, m5epd_update_mode_t mode);

    int judge_touched_button_id(int x, int y);
    int search_executable_button_id();

private:
    std::vector<ui_object> button_list_;
    std::vector<ui_object> object_list_;

    std::map<int, ui_object> *id_to_button_dic_;
    std::map<int, ui_object> *id_to_object_dic_;

    id_generator button_id_generator;

    std::vector<ui_label> label_list_;

    M5EPD_Canvas *canvas_;
    String font_file_path_;

    position tmp_touch_point_ = {0, 0};
    position target_touch_point_ = {0, 0};
    bool touch_flag_ = false;
};

#endif
