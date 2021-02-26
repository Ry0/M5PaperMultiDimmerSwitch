#include "ui_object.h"

ui_object::ui_object(int id, int x, int y, int w, int h, const uint8_t *default_image_data)
{
    this->pos_.x = x;
    this->pos_.y = y;

    this->rect_.min_pos.x = x;
    this->rect_.min_pos.y = y;
    this->rect_.max_pos.x = x + w;
    this->rect_.max_pos.y = y + h;

    this->size_.w = w;
    this->size_.h = h;

    this->default_image_data_ = default_image_data;
    this->tapped_image_data_ = nullptr;

    this->object_info_.id = id;
    this->object_info_.type = STATIC;
}

ui_object::ui_object(int id, int x, int y, int w, int h, const uint8_t *default_image_data, const uint8_t *tapped_image_data)
{
    this->pos_.x = x;
    this->pos_.y = y;

    this->rect_.min_pos.x = x;
    this->rect_.min_pos.y = y;
    this->rect_.max_pos.x = x + w;
    this->rect_.max_pos.y = y + h;

    this->size_.w = w;
    this->size_.h = h;

    this->default_image_data_ = default_image_data;
    this->tapped_image_data_ = tapped_image_data;

    this->object_info_.id = id;
    this->object_info_.type = BUTTON;
}

position ui_object::get_position()
{
    return pos_;
}

rectangle ui_object::get_rectangle()
{
    return rect_;
}

button_size ui_object::get_size()
{
    return size_;
}

const uint8_t *ui_object::get_default_image()
{
    return default_image_data_;
}

const uint8_t *ui_object::get_tapped_image()
{
    return tapped_image_data_;
}

object_info ui_object::get_object_info()
{
    return object_info_;
}
