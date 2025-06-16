// File: GameMap.c
#include "GameMap.h"

#include "raylib.h"

#include "GenList.h"
#include "Constants.h"
#include "TilesetTextures.h"

#include <string.h>
#include <stdbool.h>
#include <DrawableMetadata.h>
#include <Building.h>
#include <Constants.h>
#include <BuildingHologram.h>

typedef struct GameMap_TileVisuals {
    Drawable Floor;
    Drawable Objects;
} MapTiles;

GameMap UnitGrid[CONSTANTS_MAP_WIDTH][CONSTANTS_MAP_HEIGHT]; // O extern.
MapTiles Content[CONSTANTS_MAP_WIDTH][CONSTANTS_MAP_HEIGHT]; // Esse aqui não precisa ser conhecido por outros arquivos.

BuildingHologram buildingHologram;

void GameMap_Unload() {
    TilesetTextures_Unload();
    BuildingMetadata_Unload();
}

void GameMap_Init() {
    TilesetTextures_Load();
    BuildingMetadata_Load();

	for (int i = 0; i < CONSTANTS_MAP_WIDTH; i++) {
        for (int j = 0; j < CONSTANTS_MAP_HEIGHT; j++) {
            Content[i][j].Floor = Field.GrassVariant[0];
			Content[i][j].Floor.Position = (Vector2){ (float)i * CONSTANTS_TILE_SIZE_F, (float)j * CONSTANTS_TILE_SIZE_F };
			Content[i][j].Floor.Scale = (Vector2){ CONSTANTS_TILE_SIZE_F/48, CONSTANTS_TILE_SIZE_F/48 };
        }
	}

    BuildingHologram_Init(&buildingHologram, BUILDING_TYPE_TOWN_HALL);
    buildingHologram.IsActive = true;
}

void Map_Update() {
    BuildingHologram_Update(&buildingHologram);
}

static void DrawGridLines(int x, int y) {
    Vector2 pos = { (float)x * CONSTANTS_TILE_SIZE, (float)y * CONSTANTS_TILE_SIZE };
    DrawRectangleLines((int)pos.x, (int)pos.y, CONSTANTS_TILE_SIZE, CONSTANTS_TILE_SIZE, Fade(BLACK, 0.2f));
}

void Map_Draw() {
    for (int i = 0; i < CONSTANTS_MAP_WIDTH; i++) {
        for (int j = 0; j < CONSTANTS_MAP_HEIGHT; j++) {
            Drawable_Draw(&Content[i][j].Floor);
            DrawGridLines(i, j);
        }
    }

    BuildingHologram_Draw(&buildingHologram);
}