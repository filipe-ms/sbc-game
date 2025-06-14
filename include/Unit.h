// File: Unit.h
#pragma once

#include "Drawable.h"
#include "Animation.h"
#include "UnitAnimationMetadata.h"

#include "raylib.h"

typedef enum Unit_Type {
	UNIT_TYPE_NONE = -1,
    BARBARIAN,
} Unit_Type;

typedef struct Unit {
    Vector2* Position;
    Vector2* Scale;

    int Action;
    int Direction;
    Animation Animation;

    UnitAnimationMetadata UnitAnimationMetadata;
    Animation* Metadata;
} Unit;

// Generic Unit Methods

// Rendering / Initializing
void Unit_Init(Unit* unit, Unit_Type type);
void Unit_Update(Unit* unit);
void Unit_Draw(Unit* unit);

// Action / Direction
void Unit_ChangeAction(Unit* unit, int action);
void Unit_ChangeDirection(Unit* unit, int direction);