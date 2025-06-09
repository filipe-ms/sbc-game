// MAP_C
#include "Map.h"

#include "raylib.h"
#include "GenList.h"
#include <string.h>

Texture2D tilesetField;

const Drawable ROCK_METADATA = {
    .Texture = &tilesetField,
    .Source = { 0, 96, 48, 48 },
    .Destination = { 0 },
    .Offset = { 0, 0 },
    .Rotation = 0.0f,
    .Color = { 235, 235, 235, 255 }
};

Map_Grid Map_GameMap;

static Drawable Map_GetTileMetadata(int x, int y) {
    Drawable GROUND_METADATA = {
        .Texture = &tilesetField,
        .Source = { 48, 0, 48, 48 },
        .Destination = { (float)(x * TILE_SIZE), (float)(y * TILE_SIZE), TILE_SIZE, TILE_SIZE },
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
            Map_GameMap.Grid[i][j] = (Map_Tile){
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

void Draw_GuideLines(int x, int y) {
    Vector2 pos = { (float)x * TILE_SIZE, (float)y * TILE_SIZE };
    DrawRectangleLines((int)pos.x, (int)pos.y, TILE_SIZE, TILE_SIZE, Fade(BLACK, 0.2f));
}

void Map_Draw() {    
    for (int i = 0; i < MAP_WIDTH; i++) {
        for (int j = 0; j < MAP_HEIGHT; j++) {
            Drawable_Draw(&Map_GameMap.Grid[i][j].Floor);
            Draw_GuideLines(i, j);
        }
    }
}

/*

#include "stdio.h"
#include "raymath.h"
#include "definitions.h"
#include "unit.h"
#include "draw.h"
#include "MathUtils.h"

void InitMap(GameMap* map) {
    if (!map) {
        TraceLog(LOG_ERROR, "InitMap: ponteiro do mapa é NULL");
        return;
    }

    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            map->position[x][y].x = x;
            map->position[x][y].y = y;
            map->position[x][y].isValid = true;
            map->position[x][y].tile = GROUND;

            map->unit_occupancy_grid[x][y] = -1;
            map->tile_reservation_grid[x][y] = -1;
        }
    }

    SetTile(map, 5, 5, ROCK);
    SetTile(map, 5, 6, ROCK);
    SetTile(map, 6, 5, ROCK);
    SetTile(map, 10, 10, WALL);
    SetTile(map, 10, 11, WALL);
    SetTile(map, 10, 12, WALL);
}

static void OccupyTile(GameMap* map, int x, int y, int unit_id) {
    if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT) {
        map->unit_occupancy_grid[x][y] = unit_id;
    }
}

void UpdateUnitOccupancyGrid(GameMap* map, UnitNode* units_head) {
    if (!map) {
        TraceLog(LOG_WARNING, "UpdateUnitOccupancyGrid: ponteiro do mapa é NULL");
        return;
    }

    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            map->unit_occupancy_grid[x][y] = -1;
        }
    }

    UnitNode* current_node = units_head;
    while (current_node != NULL) {
        if (current_node->unit && current_node->unit->position.isValid) {
            Unit* unit = current_node->unit;
            GridPosition unit_base_pos = unit->position;

            OccupyTile(map, unit_base_pos.x, unit_base_pos.y, unit->id);

            if (unit->type == BUILDING)
            {
                int px = unit_base_pos.x;
                int py = unit_base_pos.y;
                switch (unit->subtype)
                {
                case(TOWN_HALL):
                    OccupyTile(map, px - 1, py, unit->id);
                    OccupyTile(map, px + 1, py, unit->id);
                    OccupyTile(map, px, py - 1, unit->id);
                    OccupyTile(map, px - 1, py - 1, unit->id);
                    OccupyTile(map, px + 1, py - 1, unit->id);
                    OccupyTile(map, px, py - 2, unit->id);
                    break;
                case(TENT):
                    OccupyTile(map, px + 1, py, unit->id);
                    OccupyTile(map, px, py - 1, unit->id);
                    OccupyTile(map, px + 1, py - 1, unit->id);
                    break;
                case(MARKETPLACE):
                    OccupyTile(map, px + 1, py, unit->id);
                    OccupyTile(map, px, py - 1, unit->id);
                    OccupyTile(map, px + 1, py - 1, unit->id);
                    break;
                }
            }
        }
        current_node = current_node->next;
    }
}

void SetTile(GameMap* map, int x, int y, TileType tile) {
    if (map && x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT) {
        map->position[x][y].tile = tile;
    }
}

TileType GetTile(GameMap* map, int x, int y) {
    if (map && x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT) {
        return map->position[x][y].tile;
    }
    return TILE_INVALID;
}

bool IsTileObstacle(GameMap* map, int x, int y) {
    if (!map) return true;
    if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT) {
        return true;
    }

    TileType type = map->position[x][y].tile;
    return type == ROCK || type == WALL;
}

bool IsPositionWalkable(GameMap* map, int x, int y, int asking_unit_id) {
    if (!map) return false;

    if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT) {
        return false;
    }

    if (IsTileObstacle(map, x, y)) {
        return false;
    }

    int occupying_unit_id = map->unit_occupancy_grid[x][y];
    if (occupying_unit_id != -1 && occupying_unit_id != asking_unit_id) {
        return false;
    }

    int reservation_owner_id = map->tile_reservation_grid[x][y];
    if (reservation_owner_id != -1 && reservation_owner_id != asking_unit_id) {
        return false;
    }

    return true;
}

bool IsValidGridPosition(GridPosition pos) {
    return pos.x >= 0 && pos.x < MAP_WIDTH &&
        pos.y >= 0 && pos.y < MAP_HEIGHT;
}

int HashVariant(int x, int y, int max_variant) {
    unsigned int hash = (unsigned int)(x * 73856093 ^ y * 19349663);
    return hash % max_variant;
}

static void DrawGround(GameMap* map) {
    if (!map) return;
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            Vector2 pos = { (float)x * TILE_SIZE, (float)y * TILE_SIZE };
            DrawTile(pos, GROUND, 0);

            int hash1 = HashVariant(x, y, 100);
            if (hash1 < 20) {
                int variant1 = HashVariant(x, y, 10);
                DrawOrnament(pos, variant1);
            }
            int hash2 = HashVariant(y, x, 100);
            if (hash2 < 20) {
                int variant2 = HashVariant(y, x, 25);
                DrawOrnament2(pos, variant2);
            }
            DrawRectangleLines((int)pos.x, (int)pos.y, TILE_SIZE, TILE_SIZE, Fade(BLACK, 0.2f)); // isso aqui é a grid
        }
    }
}

static void DrawRock(GameMap* map, Vector2 pos, int x_grid, int y_grid) {
    int variant = HashVariant(x_grid, y_grid, 10);
    DrawTile(pos, ROCK, variant);
}

void DrawMap(GameMap* map) {
    if (!map) return;
    DrawGround(map);

    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            Vector2 tile_world_pos = { (float)x * TILE_SIZE, (float)y * TILE_SIZE };
            TileType tile_type = map->position[x][y].tile;

            switch (tile_type) {
            case GROUND:
                break;
            case ROCK:
                DrawRock(map, tile_world_pos, x, y);
                break;
            case WALL:
                DrawRectangleV(tile_world_pos, (Vector2) { TILE_SIZE, TILE_SIZE }, DARKGRAY);
                break;
            case TILE_INVALID:
                break;
            default:
                break;
            }
        }
    }
}

void UnloadMap(GameMap* map) {
    if (map) {
        printf("Recursos do mapa descarregados (se houver).\n");
    }
}

GridPosition GetTileAtPosition(GameMap* map, Vector2 world_position) {
    GridPosition grid_pos;

    if (!map) {
        grid_pos.x = -1;
        grid_pos.y = -1;
        grid_pos.isValid = false;
        grid_pos.tile = TILE_INVALID;
        return grid_pos;
    }

    grid_pos.x = (int)(world_position.x / TILE_SIZE);
    grid_pos.y = (int)(world_position.y / TILE_SIZE);

    if (grid_pos.x >= 0 && grid_pos.x < MAP_WIDTH && grid_pos.y >= 0 && grid_pos.y < MAP_HEIGHT) {
        grid_pos.isValid = true;
        grid_pos.tile = map->position[grid_pos.x][grid_pos.y].tile;
    }
    else {
        grid_pos.isValid = false;
        grid_pos.tile = TILE_INVALID;
    }
    return grid_pos;
}

void ClearTileReservation(GameMap* map, GridPosition tile_pos) {
    if (map && tile_pos.isValid && IsValidGridPosition(tile_pos)) {
        map->tile_reservation_grid[tile_pos.x][tile_pos.y] = -1;
    }
}

void SetTileReservation(GameMap* map, GridPosition tile_pos, int unit_id) {
    if (map && tile_pos.isValid && IsValidGridPosition(tile_pos)) {
        map->tile_reservation_grid[tile_pos.x][tile_pos.y] = unit_id;
    }
}

int GetTileReservationOwner(GameMap* map, GridPosition tile_pos) {
    if (map && tile_pos.isValid && IsValidGridPosition(tile_pos)) {
        return map->tile_reservation_grid[tile_pos.x][tile_pos.y];
    }
    return -1;
}*/