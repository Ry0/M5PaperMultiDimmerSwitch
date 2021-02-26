#ifndef _DATA_STRUCT_H_
#define _DATA_STRUCT_H_

typedef struct position
{
    int x;
    int y;
};

typedef struct button_size
{
    int w;
    int h;
};

typedef struct rectangle
{
    position min_pos;
    position max_pos;
};

typedef enum
{
    STATIC,
    BUTTON,
} ui_type;

typedef struct object_info
{
    int id;
    ui_type type;
};

typedef enum
{
    button_event_single_press,
    button_event_double_press,
    button_event_long_press,
} button_event_t;

#endif