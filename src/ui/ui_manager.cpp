#include "ui_manager.h"
#include "../resources/binaryttf.h"

ui_manager::ui_manager(M5EPD_Canvas *canvas)
{
    canvas_ = canvas;
}

void ui_manager::create_button(int x, int y, int w, int h, const uint8_t *default_image_data, const uint8_t *tapped_image_data)
{
    int id = button_id_generator.get_id();
    ui_object o(id, x, y, w, h, default_image_data, tapped_image_data);
    button_list_.push_back(o);
}

void ui_manager::create_object(int x, int y, int w, int h, const uint8_t *image_data)
{
    int id = -1;
    ui_object o(id, x, y, w, h, image_data);
    object_list_.push_back(o);
}

void ui_manager::create_label(int x, int y, uint8_t size, uint16_t color, uint16_t cache_size, String title)
{
    ui_label l(x, y, size, color, cache_size, title);
    label_list_.push_back(l);
}

void ui_manager::initialize()
{
    M5.EPD.SetRotation(90);
    M5.TP.SetRotation(90);
    M5.EPD.Clear(true);

    canvas_->createCanvas(540, 960);
    canvas_->loadFont(binaryttf, sizeof(binaryttf));
    canvas_->setTextDatum(TC_DATUM);

    button_num_ = (int)button_list_.size();
}

void ui_manager::draw_all(m5epd_update_mode_t mode)
{
    for (auto &btn : button_list_)
    {
        auto pos = btn.get_position();
        auto size = btn.get_size();
        auto image = btn.get_default_image();
        canvas_->pushImage(pos.x, pos.y, size.w, size.h, image);
    }

    for (auto &obj : object_list_)
    {
        auto pos = obj.get_position();
        auto size = obj.get_size();
        auto image = obj.get_default_image();
        canvas_->pushImage(pos.x, pos.y, size.w, size.h, image);
    }

    for (auto &lab : label_list_)
    {
        auto size = lab.get_size();
        auto cache = lab.get_cache_size();
        auto color = lab.get_color();
        auto pos = lab.get_position();
        auto title = lab.get_labal_string();

        canvas_->createRender(size, cache);
        canvas_->setTextSize(size);
        canvas_->setTextColor(color);
        canvas_->drawString(title, pos.x, pos.y);
    }

    canvas_->pushCanvas(0, 0, mode);
}

void ui_manager::draw_all_periodic(m5epd_update_mode_t mode, unsigned long period_sec)
{
    while (1)
    {
        delay(period_sec * 1000);
        Serial.printf("refresh.\n");
        draw_all(mode);
    }
}

void ui_manager::push_button(int id, m5epd_update_mode_t mode)
{
    if (0 <= id && id < button_num_)
    {
        auto pos = button_list_[id].get_position();
        auto size = button_list_[id].get_size();
        auto image = button_list_[id].get_tapped_image();
        canvas_->pushImage(pos.x, pos.y, size.w, size.h, image);
        canvas_->pushCanvas(0, 0, mode);
    }
}

void ui_manager::release_button(int id, m5epd_update_mode_t mode)
{
    if (0 <= id && id < button_num_)
    {
        auto pos = button_list_[id].get_position();
        auto size = button_list_[id].get_size();
        auto image = button_list_[id].get_default_image();
        canvas_->pushImage(pos.x, pos.y, size.w, size.h, image);
        canvas_->pushCanvas(0, 0, mode);
    }
}

int ui_manager::judge_touched_button_id(int x, int y)
{
    for (auto &bt : button_list_)
    {
        auto pos = bt.get_rectangle();
        auto id = bt.get_object_info().id;
        if (pos.min_pos.x <= x && x <= pos.max_pos.x && pos.min_pos.y <= y && y <= pos.max_pos.y)
        {
            return id;
        }
    }

    return -1;
}

int ui_manager::check_executable_button_id()
{
    if (M5.TP.avaliable())
    {
        if (!M5.TP.isFingerUp())
        {
            M5.TP.update();
            tp_finger_t FingerItem = M5.TP.readFinger(0);
            if ((tmp_touch_point_.x != FingerItem.x) || (tmp_touch_point_.y != FingerItem.y))
            {
                tmp_touch_point_.x = FingerItem.x;
                tmp_touch_point_.y = FingerItem.y;
                if (touch_flag_ == false)
                {
                    target_touch_point_.x = FingerItem.x;
                    target_touch_point_.y = FingerItem.y;
                    touch_id_ = judge_touched_button_id(target_touch_point_.x, target_touch_point_.y);
                    Serial.printf("finger ID: %d --> (x, y) = (%d, %d), size: %d, button Id: %d\r\n", FingerItem.id, FingerItem.x, FingerItem.y, FingerItem.size, touch_id_);
                    push_button(touch_id_, UPDATE_MODE_DU);
                }
                touch_flag_ = true;
            }
            else
            {
                Serial.printf("same point touch.\n");
            }
        }
        else
        {
            if (touch_flag_)
            {
                Serial.printf("finger is released.\n");
                if ((tmp_touch_point_.x == target_touch_point_.x) || (tmp_touch_point_.y == target_touch_point_.y))
                {
                    if (touch_id_ >= 0)
                    {
                        touch_flag_ = false;
                        return touch_id_;
                    }
                    else
                    {
                        Serial.printf("out of range of buttons.\n");
                    }
                }
                else
                {
                    Serial.printf("cancel motion is detected.\n");
                    release_button(touch_id_, UPDATE_MODE_DU);
                }
                touch_flag_ = false;
            }
        }
    }
    return -1;
}

int ui_manager::get_button_num()
{
    return button_num_;
}
