// File: GameMap.h
#pragma once

#include "GenList.h"
#include "Drawable.h"

#include "raylib.h"

#include <stdbool.h>

#define MAP_WIDTH 20
#define MAP_HEIGHT 20

typedef struct GameMap_TileOccupancy {
    List* Unit_OnThisTile;
    bool isWalkable;
} GameMap; // Alias

extern GameMap UnitGrid[MAP_WIDTH][MAP_HEIGHT];

void GameMap_Init(void);
void GameMap_Unload(void);
void GameMap_Update(void);
void GameMap_Draw(void);
