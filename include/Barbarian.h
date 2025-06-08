#pragma once

#include "raylib.h"
#include "Unit.h"

/*
typedef struct UnitRequestManager UnitRequestManager;

typedef enum Mood {
    NONE_MOOD = -1,
    THINKING,
    SURPRISED,
    ANGRY,
    SAD,
    HAPPY,
    NERVOUS
} Mood;

typedef enum Type {
    NONE_TYPE = -1,
    HERO,
    BUILDING,
    MONSTER
} Type;

typedef enum SubType {
    NONE_SUBTYPE = -1,
    // HEROES
    BARBARIAN,
    SORCERER,

    // ENEMIES
    SATYR,
    BEAST,
    SKELETON,

    // BOSS
    LICH,

    // BUILDINGS
    TOWN_HALL,
    TENT,
    HOUSE

} SubType;

typedef enum Direction {
    NONE_DIRECTION = -1,
    DOWN,
    LEFT,
    RIGHT,
    UP
} Direction;

typedef enum State {
    NONE_STATE = -1,
    IDLE,
    PONDERING,
    MOVING,
    ATTACKING,
    IN_COMBAT,
    FAINTING
} State;

typedef struct Attribute {
    int current;
    int max;
} Attribute;

typedef struct CombatStats {
    int level;
    Attribute health;
    Attribute mana;
    Attribute experience;
    float regen_rate;
    int attack;
    int defense;
    int attack_range;
    int sight_range;
    bool attack_ready;
    Attribute* healthptr;
    float resistance; 
} CombatStats;

typedef struct BuildStats {
    int cost;
    Attribute progress;
} BuildStats;

typedef struct Movement {
    PathList* path;
    int path_node_index;
    float speed;
} Movement;



typedef struct AiState {
    int personality;
    float request_cooldown;
    bool is_awaiting_response;
    char* previous_decisions;
} AiState;

typedef struct Unit {
    int id;
    Type type;
    SubType subtype;
    State state;
    Vector2 center;
    Rectangle box;
    GridPosition position;
    bool is_selected;
    CombatStats stats;
    BuildStats build;
    Movement movement;
    Mood mood;
    AnimationState animation;
    AnimationState expression;
    bool to_remove;

    AiState ai;

    struct Unit* target_unit;

    GridPosition reserved_destination_tile;
} Unit;
*/