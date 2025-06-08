#pragma once

#include "raylib.h"

#define TILE_SIZE 128
#define MAP_WIDTH 50
#define MAP_HEIGHT 50

/// <summary>
/// [[ Tile ], [ Tile ]]
/// List<coisas> [Ground, Ornaments]
/// List<pessoas que estão aqui>
/// </summary>

/*
typedef enum Tile {
    bool can_be_built_upon;
} Tile;

typedef enum TileType {
    TILE_NONE = -1,
    TILE_GROUND,
    TILE_ROCK,
    TILE_WALL
} TileType;

typedef struct GridPosition {
    int x;
    int y;
    bool isValid;
    TileType tile;
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

void SetTile(GameMap* map, int x, int y, TileType tile);
TileType GetTile(GameMap* map, int x, int y);
bool IsTileObstacle(GameMap* map, int x, int y);
bool IsPositionWalkable(GameMap* map, int x, int y, int asking_unit_id);
bool IsValidGridPosition(GridPosition pos);
GridPosition GetTileAtPosition(GameMap* map, Vector2 world_position);

void ClearTileReservation(GameMap* map, GridPosition tile_pos);
void SetTileReservation(GameMap* map, GridPosition tile_pos, int unit_id);
int GetTileReservationOwner(GameMap* map, GridPosition tile_pos);
*/