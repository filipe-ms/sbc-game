#pragma once
#ifndef MAP_H
#define MAP_H

#include "raylib.h"

#define TILE_SIZE 128
#define MAP_WIDTH 50
#define MAP_HEIGHT 50

typedef enum Tile {
    GROUND,
    ROCK,
    WALL,
    TILE_INVALID
} Tile;

typedef struct GridPosition {
    int x;
    int y;
    bool isValid;
    Tile tile;
} GridPosition;

typedef struct GameMap {
    GridPosition position[MAP_WIDTH][MAP_HEIGHT];
    int unit_occupancy_grid[MAP_WIDTH][MAP_HEIGHT];
    int tile_reservation_grid[MAP_WIDTH][MAP_HEIGHT];
} GameMap;

void InitMap(GameMap* map);
void DrawMap(GameMap* map);
void UnloadMap(GameMap* map);

struct UnitNode;
void UpdateUnitOccupancyGrid(GameMap* map, struct UnitNode* units_head);

void SetTile(GameMap* map, int x, int y, Tile tile);
Tile GetTile(GameMap* map, int x, int y);
bool IsTileObstacle(GameMap* map, int x, int y);
bool IsPositionWalkable(GameMap* map, int x, int y, int asking_unit_id);
bool IsValidGridPosition(GridPosition pos);
GridPosition GetTileAtPosition(GameMap* map, Vector2 world_position);

void ClearTileReservation(GameMap* map, GridPosition tile_pos);
void SetTileReservation(GameMap* map, GridPosition tile_pos, int unit_id);
int GetTileReservationOwner(GameMap* map, GridPosition tile_pos);

#endif // MAP_H
