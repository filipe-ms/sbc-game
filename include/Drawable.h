#pragma once

#include <raylib.h>

typedef struct Drawable_Metadata {
    Texture2D* Texture;
    Rectangle Source;
    Rectangle Destination;
    Vector2 Offset;
    float Rotation;
    Color Color;
} Drawable_Metadata;

void Drawable_Draw(Drawable_Metadata* drawable);