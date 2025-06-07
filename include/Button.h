// BUTTON_H
#pragma once

#include "raylib.h"

typedef struct Button {
    Rectangle bounds;
    char* text;
    int font_size;
    Color color;
    Color hover_color;
} Button;

void Button_Draw(Button* button);