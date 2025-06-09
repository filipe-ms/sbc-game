#pragma once

#include <raylib.h>

typedef struct Drawable {
    Texture2D* Texture;
    Rectangle Source;
    Rectangle Destination;
    Vector2 Offset;
    float Rotation;
    Color Color;
} Drawable;

void Drawable_Draw(Drawable* drawable);