// File: MiniMap.h
#pragma once

#include "raylib.h"

typedef struct MiniMap {
	Vector2 Postition;
	Vector2 Size;
	float BorderSize;
	float Zoom;
	Color BorderColor;
	Color BackgroundColor;
} MiniMap;

extern MiniMap Minimap;

void MiniMap_Init(Vector2 position, Vector2 size, float borderSize, float zoom, Color borderColor, Color backgroundColor);
void MiniMap_Update(void);
void MiniMap_Draw(void);