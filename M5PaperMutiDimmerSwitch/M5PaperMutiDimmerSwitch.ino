#include <M5EPD.h>
#include "ImageResource.h"
#include "ui_manager.h"

M5EPD_Canvas canvas(&M5.EPD);
ui_manager UI(&canvas, "/GenSenRounded-R.ttf");

void setup()
{
    M5.begin();

    UI.create_button(50, 60, 190, 160, ImageResource_top_button_190x160, ImageResource_top_button_black_190x160);
    UI.create_object(50, 220, 190, 60, ImageResource_middle_button_190x60);
    UI.create_button(50, 280, 190, 160, ImageResource_bottom_button_190x160, ImageResource_bottom_button_black_190x160);

    // 右上
    UI.create_button(300, 60, 190, 160, ImageResource_top_button_190x160, ImageResource_top_button_black_190x160);
    UI.create_object(300, 220, 190, 60, ImageResource_middle_button_190x60);
    UI.create_button(300, 280, 190, 160, ImageResource_bottom_button_190x160, ImageResource_bottom_button_black_190x160);

    // 左下
    UI.create_button(50, 60 + 460, 190, 160, ImageResource_top_button_190x160, ImageResource_top_button_black_190x160);
    UI.create_object(50, 220 + 460, 190, 60, ImageResource_middle_button_190x60);
    UI.create_button(50, 280 + 460, 190, 160, ImageResource_bottom_button_190x160, ImageResource_bottom_button_black_190x160);

    // 右下
    UI.create_button(300, 60 + 460, 190, 160, ImageResource_top_button_190x160, ImageResource_top_button_black_190x160);
    UI.create_object(300, 220 + 460, 190, 60, ImageResource_middle_button_190x60);
    UI.create_button(300, 280 + 460, 190, 160, ImageResource_bottom_button_190x160, ImageResource_bottom_button_black_190x160);

    // ラベル
    UI.create_label(145, 242, 24, 15, 256, "シーリングライト");
    UI.create_label(395, 242, 24, 15, 256, "デスクライト");
    UI.create_label(145, 700, 24, 15, 256, "テレビ");
    UI.create_label(395, 700, 24, 15, 256, "エアコン");

    UI.initialize();

    UI.draw_all(UPDATE_MODE_GC16);
}

void loop()
{
    int id = UI.search_executable_button_id();
    if (id >= 0)
    {
        Serial.printf("touched id = %d\n", id);

        UI.release_button(id, UPDATE_MODE_DU);
    }
}