#include "ui_label.h"

ui_label::ui_label(int x, int y, uint8_t size, uint16_t color, uint16_t cache_size, String title)
{
    label_pos_.x = x;
    label_pos_.y = y;

    label_size_ = size;
    label_color_ = color;
    label_cache_size_ = cache_size;
    title_ = title;
}

position ui_label::get_position()
{
    return label_pos_;
}

uint8_t ui_label::get_size()
{
    return label_size_;
}

uint16_t ui_label::get_color()
{
    return label_color_;
}

uint16_t ui_label::get_cache_size()
{
    return label_cache_size_;
}

String ui_label::get_labal_string()
{
    return title_;
}