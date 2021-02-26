#ifndef _DATA_STRUCT_H_
#define _DATA_STRUCT_H_

typedef struct
{
    int x;
    int y;
} position;

typedef struct
{
    int w;
    int h;
} button_size;

typedef struct
{
    position min_pos;
    position max_pos;
} rectangle;

typedef enum
{
    STATIC,
    BUTTON,
} ui_type;

typedef struct
{
    int id;
    ui_type type;
} object_info;

typedef enum
{
    button_event_single_press,
    button_event_double_press,
    button_event_long_press,
} button_event_t;

#endif