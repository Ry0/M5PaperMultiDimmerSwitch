#include <M5EPD.h>
#include "ImageResource.h"

M5EPD_Canvas canvas(&M5.EPD);
int point[2];
int target_point[2];
bool touch_flag = false;

void setup()
{
    M5.begin();
    M5.EPD.SetRotation(90);
    M5.TP.SetRotation(90);
    M5.EPD.Clear(true);
    canvas.createCanvas(540, 960);

    // 左上
    canvas.pushImage(50, 60, 190, 160, ImageResource_top_button_190x160);
    canvas.pushImage(50, 220, 190, 60, ImageResource_middle_button_190x60);
    canvas.pushImage(50, 280, 190, 160, ImageResource_bottom_button_190x160);

    // 右上
    canvas.pushImage(300, 60, 190, 160, ImageResource_top_button_190x160);
    canvas.pushImage(300, 220, 190, 60, ImageResource_middle_button_190x60);
    canvas.pushImage(300, 280, 190, 160, ImageResource_bottom_button_190x160);

    // 左下
    canvas.pushImage(50, 60 + 460, 190, 160, ImageResource_top_button_190x160);
    canvas.pushImage(50, 220 + 460, 190, 60, ImageResource_middle_button_190x60);
    canvas.pushImage(50, 280 + 460, 190, 160, ImageResource_bottom_button_190x160);

    // 右下
    canvas.pushImage(300, 60 + 460, 190, 160, ImageResource_top_button_190x160);
    canvas.pushImage(300, 220 + 460, 190, 60, ImageResource_middle_button_190x60);
    canvas.pushImage(300, 280 + 460, 190, 160, ImageResource_bottom_button_190x160);

    // 文字
    canvas.loadFont("/GenSenRounded-R.ttf", SD);

    canvas.createRender(24, 256);
    canvas.setTextSize(24);
    canvas.setTextColor(15);
    canvas.setTextDatum(TC_DATUM);
    canvas.drawString("シーリングライト", 145, 242);
    canvas.drawString("デスクライト", 395, 242);
    canvas.drawString("テレビ", 145, 700);
    canvas.drawString("エアコン", 395, 700);

    canvas.pushCanvas(0, 0, UPDATE_MODE_GC16);
}

void loop()
{

    if (M5.TP.avaliable())
    {
        if (!M5.TP.isFingerUp())
        {
            M5.TP.update();
            bool is_update = false;

            tp_finger_t FingerItem = M5.TP.readFinger(0);
            if ((point[0] != FingerItem.x) || (point[1] != FingerItem.y))
            {
                is_update = true;
                point[0] = FingerItem.x;
                point[1] = FingerItem.y;
                if (touch_flag == false)
                {
                    target_point[0] = FingerItem.x;
                    target_point[1] = FingerItem.y;
                    int result = JudgeTouchButton(FingerItem.x, FingerItem.y);
                    Serial.printf("Finger ID:%d--> (X, y) = (%d, %d) Size: %d Judge: %d\r\n", FingerItem.id, FingerItem.x, FingerItem.y, FingerItem.size, result);
                    PushButton(result);
                }

                touch_flag = true;
            }
            else
            {
                Serial.printf("same point touch\n");
            }

            if (is_update)
            {
                Serial.printf("is_update is true\n");
                // canvas.pushCanvas(0, 0, UPDATE_MODE_DU4);
            }
        }
        else
        {
            if (touch_flag)
            {
                Serial.printf("touch_flag is true\n");
                if ((point[0] == target_point[1]) || (point[1] == target_point[1]))
                {
                    int result = JudgeTouchButton(point[0], point[1]);
                    ReleaseButton(result);
                    if (result > 0)
                    {
                        Serial.printf("!!!execute!!!\n");
                    }
                }
                else
                {
                    Serial.printf("not execute!\n");
                    int result = JudgeTouchButton(target_point[0], target_point[1]);
                    ReleaseButton(result);
                }

                touch_flag = false;
            }
            else
            {
                // Serial.printf("touch_flag is false\n");
            }
        }
    }
}

int JudgeTouchButton(int x, int y)
{
    if (50 <= x && x <= 240)
    {
        if (60 <= y && y <= 220)
        {
            return 1;
        }
        else if (280 <= y && y <= 440)
        {
            return 2;
        }
        else if (520 <= y && y <= 680)
        {
            return 5;
        }
        else if (740 <= y && y <= 900)
        {
            return 6;
        }
        else
        {
            return -1;
        }
    }
    else if (300 <= x && x <= 490)
    {
        if (60 <= y && y <= 220)
        {
            return 3;
        }
        else if (280 <= y && y <= 440)
        {
            return 4;
        }
        else if (520 <= y && y <= 680)
        {
            return 7;
        }
        else if (740 <= y && y <= 900)
        {
            return 8;
        }
        else
        {
            return -1;
        }
    }
    else
    {
        return -1;
    }
}

void PushButton(int button_id)
{

    switch (button_id)
    {
    case 1:
        canvas.pushImage(50, 60, 190, 160, ImageResource_top_button_black_190x160);
        canvas.pushCanvas(0, 0, UPDATE_MODE_DU);
        Serial.printf("button %d is pushed.\n", button_id);
        break;
    case 2:
        canvas.pushImage(50, 280, 190, 160, ImageResource_bottom_button_black_190x160);
        canvas.pushCanvas(0, 0, UPDATE_MODE_DU);
        Serial.printf("button %d is pushed.\n", button_id);
        break;
    case 3:
        canvas.pushImage(300, 60, 190, 160, ImageResource_top_button_black_190x160);
        canvas.pushCanvas(0, 0, UPDATE_MODE_DU);
        Serial.printf("button %d is pushed.\n", button_id);
        break;
    case 4:
        canvas.pushImage(300, 280, 190, 160, ImageResource_bottom_button_black_190x160);
        canvas.pushCanvas(0, 0, UPDATE_MODE_DU);
        Serial.printf("button %d is pushed.\n", button_id);
        break;
    case 5:
        canvas.pushImage(50, 60 + 460, 190, 160, ImageResource_top_button_black_190x160);
        canvas.pushCanvas(0, 0, UPDATE_MODE_DU);
        Serial.printf("button %d is pushed.\n", button_id);
        break;
    case 6:
        canvas.pushImage(50, 280 + 460, 190, 160, ImageResource_bottom_button_black_190x160);
        canvas.pushCanvas(0, 0, UPDATE_MODE_DU);
        Serial.printf("button %d is pushed.\n", button_id);
        break;
    case 7:
        canvas.pushImage(300, 60 + 460, 190, 160, ImageResource_top_button_black_190x160);
        canvas.pushCanvas(0, 0, UPDATE_MODE_DU);
        Serial.printf("button %d is pushed.\n", button_id);
        break;
    case 8:
        canvas.pushImage(300, 280 + 460, 190, 160, ImageResource_bottom_button_black_190x160);
        canvas.pushCanvas(0, 0, UPDATE_MODE_DU);
        Serial.printf("button %d is pushed.\n", button_id);
        break;
    default:
        Serial.printf("button is not pushed.\n", button_id);
    }
}

void ReleaseButton(int button_id)
{

    switch (button_id)
    {
    case 1:
        canvas.pushImage(50, 60, 190, 160, ImageResource_top_button_190x160);
        canvas.pushCanvas(0, 0, UPDATE_MODE_DU);
        Serial.printf("button %d is released.\n", button_id);
        break;
    case 2:
        canvas.pushImage(50, 280, 190, 160, ImageResource_bottom_button_190x160);
        canvas.pushCanvas(0, 0, UPDATE_MODE_DU);
        Serial.printf("button %d is released.\n", button_id);
        break;
    case 3:
        canvas.pushImage(300, 60, 190, 160, ImageResource_top_button_190x160);
        canvas.pushCanvas(0, 0, UPDATE_MODE_DU);
        Serial.printf("button %d is released.\n", button_id);
        break;
    case 4:
        canvas.pushImage(300, 280, 190, 160, ImageResource_bottom_button_190x160);
        canvas.pushCanvas(0, 0, UPDATE_MODE_DU);
        Serial.printf("button %d is released.\n", button_id);
        break;
    case 5:
        canvas.pushImage(50, 60 + 460, 190, 160, ImageResource_top_button_190x160);
        canvas.pushCanvas(0, 0, UPDATE_MODE_DU);
        Serial.printf("button %d is released.\n", button_id);
        break;
    case 6:
        canvas.pushImage(50, 280 + 460, 190, 160, ImageResource_bottom_button_190x160);
        canvas.pushCanvas(0, 0, UPDATE_MODE_DU);
        Serial.printf("button %d is released.\n", button_id);
        break;
    case 7:
        canvas.pushImage(300, 60 + 460, 190, 160, ImageResource_top_button_190x160);
        canvas.pushCanvas(0, 0, UPDATE_MODE_DU);
        Serial.printf("button %d is released.\n", button_id);
        break;
    case 8:
        canvas.pushImage(300, 280 + 460, 190, 160, ImageResource_bottom_button_190x160);
        canvas.pushCanvas(0, 0, UPDATE_MODE_DU);
        Serial.printf("button %d is released.\n", button_id);
        break;
    default:
        Serial.printf("button is not released.\n", button_id);
    }
}