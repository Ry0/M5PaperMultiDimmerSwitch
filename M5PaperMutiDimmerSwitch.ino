#include <M5EPD.h>

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
    canvas.setTextSize(5);
    canvas.drawString("Touch The Screen!", 20, 400);
    canvas.pushCanvas(0, 0, UPDATE_MODE_DU4);
}

void loop()
{

    if (M5.TP.avaliable())
    {
        if (!M5.TP.isFingerUp())
        {
            M5.TP.update();
            canvas.fillCanvas(0);
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
                    canvas.fillRect(FingerItem.x - 50, FingerItem.y - 50, 100, 100, 15);
                    // Serial.printf("Finger ID:%d-->X: %d*C  Y: %d  Size: %d\r\n", FingerItem.id, FingerItem.x, FingerItem.y, FingerItem.size);
                }

                touch_flag = true;
            }
            else
            {
                // Serial.printf("same point touch\n");
            }

            if (is_update)
            {
                // Serial.printf("is_update is true\n");
                canvas.pushCanvas(0, 0, UPDATE_MODE_DU4);
            }
        }
        else
        {
            if (touch_flag)
            {
                // Serial.printf("touch_flag is true\n");
                if ((point[0] == target_point[1]) || (point[1] == target_point[1]))
                {
                    Serial.printf("!!!execute!!!\n");
                }

                canvas.fillCanvas(0);
                canvas.pushCanvas(0, 0, UPDATE_MODE_DU4);
                touch_flag = false;
            }
            else
            {
                // Serial.printf("touch_flag is false\n");
            }
        }
    }
}