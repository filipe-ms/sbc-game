// File: TilesetTextures.h
#pragma once

#include "Drawable.h"

#include "raylib.h"


typedef struct TilesetTexture_Field {
	Drawable* GrassVariant;
	Drawable* CleanGrassVariant;
	Drawable* RockVariant;
} FieldTexture;

extern FieldTexture Field;

void TilesetTextures_Load(void);
void TilesetTextures_Unload(void);