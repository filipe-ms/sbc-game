// File: GameMap.c
#include "GameMap.h"

#include "raylib.h"

#include "GenList.h"
#include "Constants.h"
#include "TilesetTextures.h"
#include "GameCamera.h"

#include "raymath.h"

#include <string.h>
#include <stdbool.h>


typedef struct GameMap_TileVisuals {
    Drawable Floor;
    Drawable Objects;
} MapTiles;

GameMap UnitGrid[MAP_WIDTH][MAP_HEIGHT]; // O extern.
MapTiles Content[MAP_WIDTH][MAP_HEIGHT]; // Esse aqui não precisa ser conhecido por outros arquivos.

void GameMap_Unload() {
    TilesetTextures_Unload();
}

void GameMap_Init() {
    TilesetTextures_Load();


	for (int i = 0; i < MAP_WIDTH; i++) {
        for (int j = 0; j < MAP_HEIGHT; j++) {
            Content[i][j].Floor = Field.GrassVariant[0];
			Content[i][j].Floor.Position = (Vector2){ (float)i * CONSTANTS_TILE_SIZE_F, (float)j * CONSTANTS_TILE_SIZE_F };
			Content[i][j].Floor.Scale = (Vector2){ CONSTANTS_TILE_SIZE_F/48, CONSTANTS_TILE_SIZE_F/48 };
        }
	}
}

void GameMap_Update() {}

static void DrawGridLines(int x, int y) {
    Vector2 pos = { (float)x * CONSTANTS_TILE_SIZE, (float)y * CONSTANTS_TILE_SIZE };
    DrawRectangleLines((int)pos.x, (int)pos.y, CONSTANTS_TILE_SIZE, CONSTANTS_TILE_SIZE, Fade(BLACK, 0.2f));
}

void GameMap_Draw() {
    int startingDrawPosX = (int)(GameCamera.target.x / CONSTANTS_TILE_SIZE_F);
    int startingDrawPosY = (int)(GameCamera.target.y / CONSTANTS_TILE_SIZE_F);

    int endDrawPosX = (int)((GameCamera.target.x + CONSTANTS_VIDEO_SETTINGS_WIDTH_BUFFER) / CONSTANTS_TILE_SIZE_F) + 2;
    int endDrawPosY = (int)((GameCamera.target.y + CONSTANTS_VIDEO_SETTINGS_HEIGHT_BUFFER) / CONSTANTS_TILE_SIZE_F) + 2;

    startingDrawPosX = (int)Clamp(startingDrawPosX, 0, MAP_WIDTH);
    startingDrawPosY = (int)Clamp(startingDrawPosY, 0, MAP_HEIGHT);
    endDrawPosX = (int)Clamp(endDrawPosX, 0, MAP_WIDTH);
    endDrawPosY = (int)Clamp(endDrawPosY, 0, MAP_HEIGHT);

    for (int i = startingDrawPosX; i < endDrawPosX; i++) {
        for (int j = startingDrawPosY; j < endDrawPosY; j++) {
            Drawable_Draw(&Content[i][j].Floor);
            DrawGridLines(i, j);
        }
    }
}