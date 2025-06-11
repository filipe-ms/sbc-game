// MAP_C
#include "GameMap.h"

#include "raylib.h"

#include "GenList.h"
#include "Constants.h"

#include <string.h>

Texture2D tilesetField;

const Drawable ROCK_METADATA = {
    .Texture = &tilesetField,
    .Source = { 0, 96, 48, 48 },
	.Position = { 0, 0 },
	.Scale = { 0, 0 },
    .Offset = { 0, 0 },
    .Rotation = 0.0f,
    .Color = { 235, 235, 235, 255 }
};

Map_Grid GameMap;

static Drawable Map_GetTileMetadata(int x, int y) {
    Drawable GROUND_METADATA = {
        .Texture = &tilesetField,
        .Source = { 48, 0, 48, 48 },
		.Position = { (float)(x * CONSTANTS_TILE_SIZE_F), (float)(y * CONSTANTS_TILE_SIZE_F) },
		.Scale = { CONSTANTS_TILE_SIZE_F / 48, CONSTANTS_TILE_SIZE_F / 48 },
        .Offset = { 0 },
        .Rotation = 0.0f,
        .Color = { 240, 240, 240, 225 }
    };
    
    return GROUND_METADATA;
};


void Map_Init() {
    tilesetField = LoadTexture("tileset/field.png");

    for (int i = 0; i < MAP_WIDTH; i++) {
        for (int j = 0; j < MAP_HEIGHT; j++) {
            GameMap.Grid[i][j] = (Map_Tile){
                .Floor = Map_GetTileMetadata(i, j),
                .Unit_OnThisTile = List_Create(sizeof(int))
            };
        }
    }
}

void Map_Unload() {
    UnloadTexture(tilesetField);
}

void Map_Update() {

}

static void DrawGridLines(int x, int y) {
    Vector2 pos = { (float)x * TILE_SIZE, (float)y * TILE_SIZE };
    DrawRectangleLines((int)pos.x, (int)pos.y, TILE_SIZE, TILE_SIZE, Fade(BLACK, 0.2f));
}

void Map_Draw() {    
    for (int i = 0; i < MAP_WIDTH; i++) {
        for (int j = 0; j < MAP_HEIGHT; j++) {
            Drawable_Draw(&GameMap.Grid[i][j].Floor);
            DrawGridLines(i, j);
        }
    }
}