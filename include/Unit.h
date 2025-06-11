#pragma once

#include "raylib.h"

#include "Drawable.h"
#include "Animation.h"
#include "UnitAnimationMetadata.h"

typedef enum Unit_Type {
    BARBARIAN,
} Unit_Type;

typedef struct Unit {
    Vector2* Position;
    int Action;
    int Direction;
    Animation Animation;

    Unit_Type unitAnimationMetadata;

    UnitAnimationMetadata UnitAnimationMetadata;
    Animation* Metadata;
} Unit;

// Generic Unit Methods

// Rendering / Initializing
void Unit_Init(Unit* unit, Unit_Type type);
void Unit_Update(Unit* unit);
void Unit_Draw(Unit* unit);
void Unit_Load(void);
void Unit_Unload(void);

// Action / Direction
void Unit_ChangeAction(Unit* unit, int action);
void Unit_ChangeDirection(Unit* unit, int direction);