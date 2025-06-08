#pragma once

#include "raylib.h"
#include "Drawable.h"
#include "AnimationState.h"

typedef enum Direction {
    DIRECTION_NONE = -1,
    DIRECTION_DOWN = 0,
    DIRECTION_LEFT = 1,
    DIRECTION_RIGHT = 2,
    DIRECTION_UP = 3
} Direction;

typedef struct Unit {
    int Id;
    Direction Direction;
    AnimationState Animation;
} Unit;

void Unit_Init(Unit* unit);
void Unit_Load(void);
void Unit_Update(Unit* unit);
void Unit_Unload(void);
void Unit_Draw(Unit* unit);