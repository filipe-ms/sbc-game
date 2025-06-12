// File: GameMap.c
#include "GameMap.h"

#include "raylib.h"

#include "GenList.h"
#include "Constants.h"

#include <string.h>
#include <stdbool.h>

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

    // Definição de obstáculos (layout movido para cá)
#define o true  // open (caminhável)
#define r false // restricted (obstáculo)
    bool obstacleLayout[MAP_HEIGHT][MAP_WIDTH] = {
        {o, o, o, o, o, o, o, o, o, o, o, o, o, r, o, o, o, o, o, o},
        {o, o, o, o, o, o, r, r, r, r, r, r, o, r, o, r, r, r, r, o},
        {o, o, o, o, o, o, o, o, o, o, o, r, o, r, o, o, o, o, r, o},
        {o, o, o, o, o, r, r, r, o, r, o, o, o, o, o, o, r, o, r, o},
        {o, o, o, o, o, o, o, o, o, r, o, o, o, o, o, o, r, o, r, o},
        {o, o, o, o, o, o, o, o, o, r, o, o, o, o, o, o, o, o, r, o},
        {o, r, o, o, o, o, o, o, o, r, o, o, o, o, r, o, r, o, r, o},
        {o, r, o, o, r, r, o, o, o, o, o, o, o, o, r, o, o, o, r, o},
        {o, r, o, r, o, o, o, o, o, o, o, o, o, o, r, o, r, o, r, o},
        {o, r, o, r, o, o, o, o, r, r, r, o, o, o, r, o, r, o, r, o},
        {o, o, o, r, o, r, o, o, o, o, r, o, r, o, o, o, r, o, r, o},
        {r, r, r, r, o, r, r, r, r, o, r, o, r, r, r, o, r, o, r, o},
        {o, o, o, o, o, o, o, o, r, o, r, o, o, o, o, o, r, o, r, o},
        {o, r, r, r, r, r, r, o, r, o, r, r, r, r, r, o, r, o, r, o},
        {o, r, o, o, o, o, r, o, r, o, o, o, o, o, r, o, r, o, o, o},
        {o, r, o, r, r, o, r, o, r, r, r, r, r, o, r, o, r, r, r, o},
        {o, r, o, r, o, o, r, o, o, o, o, o, r, o, r, o, o, o, r, o},
        {o, r, o, r, o, r, r, r, r, r, r, o, r, o, r, r, r, o, r, o},
        {o, r, o, o, o, o, o, o, o, o, r, o, o, o, o, o, o, o, o, o},
        {o, o, o, r, r, r, r, r, r, o, o, o, r, r, r, r, r, r, r, o}
    };
#undef o
#undef r

    for (int i = 0; i < MAP_WIDTH; i++) { // i corresponde a x
        for (int j = 0; j < MAP_HEIGHT; j++) { // j corresponde a y
            GameMap.Grid[i][j] = (Map_Tile){
                .Floor = Map_GetTileMetadata(i, j),
                .Unit_OnThisTile = List_Create(sizeof(int)),
                .isWalkable = obstacleLayout[j][i]
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
    Vector2 pos = { (float)x * CONSTANTS_TILE_SIZE, (float)y * CONSTANTS_TILE_SIZE };
    DrawRectangleLines((int)pos.x, (int)pos.y, CONSTANTS_TILE_SIZE, CONSTANTS_TILE_SIZE, Fade(BLACK, 0.2f));
}

void Map_Draw() {
    for (int i = 0; i < MAP_WIDTH; i++) {
        for (int j = 0; j < MAP_HEIGHT; j++) {
            // Desenha o chão primeiro
            Drawable_Draw(&GameMap.Grid[i][j].Floor);

            if (!GameMap.Grid[i][j].isWalkable) {
                int variant = 0;
                Drawable rock = {
                    .Texture = &tilesetField,
                    .Source = { (float)(288 + 48 * variant), 96, 48, 48 },
                    .Position = GameMap.Grid[i][j].Floor.Position,
                    .Scale = GameMap.Grid[i][j].Floor.Scale,
                    .Offset = { 0, 0 },
                    .Rotation = 0.0f,
                    .Color = WHITE
                };
                Drawable_Draw(&rock);
            }

            // Desenha as linhas do grid por cima
            DrawGridLines(i, j);
        }
    }
}