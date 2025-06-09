#pragma once

#include "raylib.h"
#include "Drawable.h"
#include "Animation.h"

typedef struct List_AnimationInstance List_AnimationInstance;

typedef enum Unit_Direction {
    UNIT_DIRECTION_NONE = -1,
    UNIT_DIRECTION_DOWN = 0,
    UNIT_DIRECTION_LEFT = 1,
    UNIT_DIRECTION_RIGHT = 2,
    UNIT_DIRECTION_UP = 3
} Unit_Direction;

typedef enum Unit_Action {
    UNIT_ACTION_NONE = -1,
    UNIT_ACTION_IDLE = 0,
    UNIT_ACTION_WALK = 1,
    UNIT_ACTION_ATTACK = 2,
    UNIT_ACTION_FAINT = 3,
} Unit_Action;

typedef struct Unit {
    int Id;
    Unit_Action Action;
    Unit_Direction Direction;
    Animation Animation;
} Unit;

typedef struct Unit_AnimationInstanceMetadata {
    Texture2D Texture;
    List_AnimationInstance* AnimationInstanceList;
} Unit_AnimationInstanceMetadata;

void Unit_Init(Unit* unit);
void Unit_Load(void);
void Unit_Update(Unit* unit);
void Unit_Unload(void);
void Unit_Draw(Unit* unit);