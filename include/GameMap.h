// File: GameMap.h
#pragma once

#include "GenList.h"
#include "Drawable.h"

#include "raylib.h"

#include <stdbool.h>

#define MAP_WIDTH 20
#define MAP_HEIGHT 20

typedef struct Map_Tile {
    Drawable Floor;
    List* Unit_OnThisTile;
    bool isWalkable;
} Map_Tile;

typedef struct {
    Map_Tile Grid[MAP_WIDTH][MAP_HEIGHT];
} Map_Grid;

extern Map_Grid GameMap;

void Map_Init(void);
void Map_Unload(void);
void Map_Update(void);
void Map_Draw(void);
