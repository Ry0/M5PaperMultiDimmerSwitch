#include <M5EPD.h>
#include "ImageResource.h"
#include "ui_manager.h"

M5EPD_Canvas canvas(&M5.EPD);
ui_manager UI(&canvas, "/GenSenRounded-R.ttf");

void setup()
{
    M5.begin();

    // define ui design
    // create_button(x, y, w, h, default_image, tap_effect_image)
    // create_object(x, y, w, h, default_image)
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

    // label
    // create_label(x, y, font_size, color, cache_size, title);
    UI.create_label(145, 242, 24, 15, 256, "シーリングライト");
    UI.create_label(395, 242, 24, 15, 256, "デスクライト");
    UI.create_label(145, 700, 24, 15, 256, "テレビ");
    UI.create_label(395, 700, 24, 15, 256, "エアコン");

    // initialize after "create_xxxx"
    UI.initialize();

    // draw the initial state of UI
    UI.draw_all(UPDATE_MODE_GC16);

    auto id_list = UI.get_button_id_list();
    for (auto &id : id_list)
    {
        Serial.printf("%d\n", id);
    }
}

void loop()
{
    int id = UI.check_executable_button_id();
    if (id >= 0)
    {
        Serial.printf("execute button!! (id = %d)\n", id);
        UI.release_button(id, UPDATE_MODE_DU);
    }
}