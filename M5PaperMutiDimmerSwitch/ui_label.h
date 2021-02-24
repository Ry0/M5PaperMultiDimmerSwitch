#ifndef _UI_LABEL_H_
#define _UI_LABEL_H_

#include <M5EPD.h>
#include <Arduino.h>
#include <FS.h>
#include "data_struct.h"

class ui_label
{
public:
    ui_label(int x, int y, uint8_t size, uint16_t color, uint16_t cache_size, String title);
    position get_position();
    uint8_t get_size();
    uint16_t get_color();
    uint16_t get_cache_size();
    String get_labal_string();

private:
    position label_pos_;
    uint8_t label_size_;
    uint16_t label_color_;
    uint16_t label_cache_size_;
    String title_;
};

#endif
