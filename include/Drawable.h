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

Drawable Drawable_Build(
    Texture2D* texture, Rectangle source, Rectangle destination,
    Vector2 offset, float rotation, Color color);

void Drawable_Draw(Drawable* drawable);