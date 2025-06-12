#pragma once

#include "raylib.h"

typedef struct Drawable { // Requerimentos do DrawTexturePRO
    Texture2D* Texture;
    Rectangle Source;
	Vector2 Position;
    Vector2 Scale;
    Vector2 Offset;
    float Rotation;
    Color Color;
} Drawable;


Drawable Drawable_Build(
    Texture2D* texture, Rectangle source, Vector2 position, Vector2 Scale,
    Vector2 offset, float rotation, Color color);

void Drawable_Draw(Drawable* drawable);

Rectangle Drawable_CalculateDestination(Drawable* drawable);