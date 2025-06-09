#pragma once

#include "raylib.h"
#include "GenList.h"
#include <Drawable.h>

#define TILE_SIZE 128
#define MAP_WIDTH 50
#define MAP_HEIGHT 50

typedef struct Map_Tile {
    Drawable Floor;
    List* Unit_OnThisTile;
} Map_Tile;

typedef struct {
    Map_Tile Grid[MAP_WIDTH][MAP_HEIGHT];
} Map_Grid;

extern Map_Grid Map_GameMap;

void Map_Init(void);
void Map_Unload(void);
void Map_Update(void);
void Map_Draw(void);

/*
Texture2D field;
field = LoadTexture("tileset/field.png");
UnloadTexture(field);
void DrawTile(Vector2 position, int tile_type, int variant) {

    Vector2 offset = { 0 };
    if (tile_type == GROUND) {
        Rectangle source = { 48, 0, 48, 48 };
        Rectangle destination = { position.x, position.y, TILE_SIZE, TILE_SIZE };
        Color c = { 240, 240, 240, 225 };
        DrawTexturePro(field, source, destination, offset, 0.0f, c);

    }
    if (tile_type == ROCK) {
        // Rock variants = 10
        if (variant > 9) variant = 9;
        if (variant < 0) variant = 0;
        float center_x = position.x + TILE_SIZE / 2;
        float center_y = position.y + TILE_SIZE / 2;
        float size = TILE_SIZE / 2;
        Rectangle source = { (float)(288 + 48 * variant), 96, 48, 48 };
        Rectangle destination = { center_x - size / 2, center_y - size / 2, size, size };
        Color color = { 235, 235, 235, 255 };
        DrawTexturePro(field, source, destination, offset, 0.0f, color);
    }
}


typedef enum Tile {
    
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