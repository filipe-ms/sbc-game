// File: GameMap.c
#include "GameMap.h"

#include "raylib.h"

#include "GenList.h"
#include "Constants.h"

#include <string.h>
#include <stdbool.h>


typedef struct GameMap_TileVisuals {
    Drawable Floor;
    Drawable* Objects;
} MapTiles;

GameMap UnitGrid[MAP_WIDTH][MAP_HEIGHT]; // O extern.
MapTiles Content[MAP_WIDTH][MAP_HEIGHT]; // Esse aqui não precisa ser conhecido por outros arquivos.

static Texture2D tilesetField;

const Drawable ROCK_METADATA = {
    .Texture = &tilesetField,
	.Source = { 288, 96, 48, 48 }, // Para outras variantes, x = 288 + 48 * variant. Total de 10 variantes.
    .Position = { 0, 0 },
    .Scale = { 0, 0 },
    .Offset = { 0, 0 },
    .Rotation = 0.0f,
    .Color = { 235, 235, 235, 255 }
};


// Utils




static Drawable Map_GetTileMetadata(int x, int y) {
    const Drawable GROUND_METADATA = {
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

static void LoadMapAssets() {
    tilesetField = LoadTexture("tileset/field.png");
}

void GameMap_Unload() {
    UnloadTexture(tilesetField);
}

void GameMap_Init() {
    LoadMapAssets();

    for (int i = 0; i < MAP_WIDTH; i++) { // i corresponde a x
        for (int j = 0; j < MAP_HEIGHT; j++) { // j corresponde a y
			Content[i][j] = (MapTiles){
				.Floor = Map_GetTileMetadata(i, j),
				.Objects = NULL // Iniciar com lista de drawable quando tiver o que colocar
			};
            UnitGrid[i][j] = (GameMap){
                .Unit_OnThisTile = List_Create(sizeof(int)),
				.isWalkable = true // Iniciar como verdadeiro e atualizar conforme as unidades, pedras, árvores etc ocupam.
            };
        }
    }
}



void Map_Update() {}

static void DrawGridLines(int x, int y) {
    Vector2 pos = { (float)x * CONSTANTS_TILE_SIZE, (float)y * CONSTANTS_TILE_SIZE };
    DrawRectangleLines((int)pos.x, (int)pos.y, CONSTANTS_TILE_SIZE, CONSTANTS_TILE_SIZE, Fade(BLACK, 0.2f));
}

void Map_Draw() {
    for (int i = 0; i < MAP_WIDTH; i++) {
        for (int j = 0; j < MAP_HEIGHT; j++) {
            Drawable_Draw(&Content[i][j].Floor);
            DrawGridLines(i, j);
        }
    }
}