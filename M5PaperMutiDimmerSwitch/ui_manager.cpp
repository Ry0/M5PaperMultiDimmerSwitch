#include "ui_manager.h"

ui_manager::ui_manager(M5EPD_Canvas *canvas, String font_file_path)
{
    canvas_ = canvas;
    font_file_path_ = font_file_path;
    // object_id_generator = id_generator();

    id_to_button_dic_ = new std::map<int, ui_object>;
    id_to_object_dic_ = new std::map<int, ui_object>;
}

void ui_manager::initialize()
{
    M5.EPD.SetRotation(90);
    M5.TP.SetRotation(90);
    M5.EPD.Clear(true);

    canvas_->createCanvas(540, 960);
    canvas_->loadFont(font_file_path_, SD);
    canvas_->setTextDatum(TC_DATUM);

    for (auto &btn : button_list_)
    {
        auto btn_info = btn.get_object_info();
        id_to_button_dic_->insert(std::make_pair(btn_info.id, btn));
    }

    for (auto &obj : object_list_)
    {
        auto obj_info = obj.get_object_info();
        id_to_object_dic_->insert(std::make_pair(obj_info.id, obj));
    }
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

void ui_manager::push_button(int id, m5epd_update_mode_t mode)
{
    if (id >= 0)
    {
        auto iter = id_to_button_dic_->find(id);
        if (iter != id_to_button_dic_->end())
        {
            Serial.printf("fill black\n");
            auto button = iter->second;
            auto pos = button.get_position();
            auto size = button.get_size();
            auto image = button.get_tapped_image();
            canvas_->pushImage(pos.x, pos.y, size.w, size.h, image);
            canvas_->pushCanvas(0, 0, mode);
        }
    }
}

void ui_manager::release_button(int id, m5epd_update_mode_t mode)
{
    if (id >= 0)
    {
        auto iter = id_to_button_dic_->find(id);
        if (iter != id_to_button_dic_->end())
        {
            auto button = iter->second;
            auto pos = button.get_position();
            auto size = button.get_size();
            auto image = button.get_default_image();
            canvas_->pushImage(pos.x, pos.y, size.w, size.h, image);
            canvas_->pushCanvas(0, 0, mode);
        }
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

int ui_manager::search_executable_button_id()
{
    if (M5.TP.avaliable())
    {
        if (!M5.TP.isFingerUp())
        {
            M5.TP.update();
            bool is_update = false;

            tp_finger_t FingerItem = M5.TP.readFinger(0);
            if ((tmp_touch_point_.x != FingerItem.x) || (tmp_touch_point_.y != FingerItem.y))
            {
                is_update = true;
                tmp_touch_point_.x = FingerItem.x;
                tmp_touch_point_.y = FingerItem.y;
                if (!touch_flag_)
                {
                    target_touch_point_.x = FingerItem.x;
                    target_touch_point_.y = FingerItem.y;
                    int touch_id = judge_touched_button_id(target_touch_point_.x, target_touch_point_.y);
                    Serial.printf("Finger ID:%d--> (X, y) = (%d, %d) Size: %d Judge: %d\r\n", FingerItem.id, FingerItem.x, FingerItem.y, FingerItem.size, touch_id);
                    push_button(touch_id, UPDATE_MODE_DU);
                }

                touch_flag_ = true;
            }
            else
            {
                Serial.printf("same point touch\n");
            }

            if (is_update)
            {
                Serial.printf("is_update is true\n");
            }
        }
        else
        {
            if (touch_flag_)
            {
                Serial.printf("touch_flag is true\n");
                if ((tmp_touch_point_.x == target_touch_point_.x) || (tmp_touch_point_.y == target_touch_point_.y))
                {
                    int touch_id = judge_touched_button_id(tmp_touch_point_.x, tmp_touch_point_.y);
                    if (touch_id >= 0)
                    {
                        return touch_id;
                    }
                }
                else
                {
                    Serial.printf("not execute!\n");
                    int touch_id = judge_touched_button_id(target_touch_point_.x, target_touch_point_.y);
                    release_button(touch_id, UPDATE_MODE_DU);
                }

                touch_flag_ = false;
            }
            else
            {
                Serial.printf("touch_flag is false\n");
            }
        }
    }

    return -1;
}