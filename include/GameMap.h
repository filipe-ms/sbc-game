// File: GameMap.h
#pragma once

#include "GenList.h"
#include "Drawable.h"

#include "raylib.h"

#include <stdbool.h>
#include <Constants.h>

typedef struct GameMap_TileOccupancy {
    List* Unit_OnThisTile;
    bool isWalkable;
} GameMap; // Alias

extern GameMap UnitGrid[CONSTANTS_MAP_WIDTH][CONSTANTS_MAP_HEIGHT];

void GameMap_Init(void);
void GameMap_Unload(void);
void Map_Update(void);
void Map_Draw(void);
