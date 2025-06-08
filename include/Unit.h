#pragma once

#include "raylib.h"
#include "Drawable.h"
#include <AnimationState.h>

typedef struct Unit {
    int id;
    AnimationState Animation;
} Unit;

void Unit_Init(Unit* unit);
void Unit_Load(void);
void Unit_Update(Unit* unit);
void Unit_Unload(void);
void Unit_Draw(Unit* unit);