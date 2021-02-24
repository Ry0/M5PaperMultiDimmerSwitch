#ifndef _UI_OBJECT_H_
#define _UI_OBJECT_H_

#include <M5EPD.h>
#include <Arduino.h>
#include <FS.h>
#include "data_struct.h"

class ui_object
{
public:
    ui_object(int id, int x, int y, int w, int h, const uint8_t *default_image_data);
    ui_object(int id, int x, int y, int w, int h, const uint8_t *default_image_data, const uint8_t *tapped_image_data);
    position get_position();
    rectangle get_rectangle();
    button_size get_size();
    object_info get_object_info();
    const uint8_t *get_default_image();
    const uint8_t *get_tapped_image();

private:
    position pos_;
    rectangle rect_;
    button_size size_;
    object_info object_info_;
    const uint8_t *default_image_data_;
    const uint8_t *tapped_image_data_;
};

#endif
