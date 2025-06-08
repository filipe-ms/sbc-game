// SpecificLists.h - Controls all list generation
#pragma once
#include "List.h"
#include "raylib.h"  // Your custom types
#include "Unit.h"

// ===== DECLARE ALL LIST TYPES =====
LIST_DECLARE(int)
LIST_DECLARE(float)
LIST_DECLARE(double)
LIST_DECLARE(Texture2D)
LIST_DECLARE(AnimationInstance)

// ===== DECLARE ALL FUNCTIONS =====
LIST_DECLARE_FUNCTIONS(int)
LIST_DECLARE_FUNCTIONS(float)
LIST_DECLARE_FUNCTIONS(double)
LIST_DECLARE_FUNCTIONS(Texture2D)
LIST_DECLARE_FUNCTIONS(AnimationInstance)

// ===== IMPLEMENTATIONS =====
#ifdef IMPLEMENT_LISTS
LIST_IMPLEMENT(int)
LIST_IMPLEMENT(float)
LIST_IMPLEMENT(double)
LIST_IMPLEMENT(Texture2D)
LIST_IMPLEMENT(AnimationInstance)
#endif