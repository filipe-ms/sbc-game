// File: TilesetTextures.h
#pragma once

#include "raylib.h"

typedef struct TilesetTexture_Field {
	Drawable* GrassVariant;
	Drawable* CleanGrassVariant;
	Drawable* RockVariant;
} FieldTexture;

extern FieldTexture Field;