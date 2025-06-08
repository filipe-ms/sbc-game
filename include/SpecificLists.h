// SpecificLists.h - Controls which lists exist
#pragma once
#include "List.h"
#include "raylib.h"
#include "Unit.h"

// Declare list types
LIST_DECLARE(int)
LIST_DECLARE(float)
LIST_DECLARE(Texture2D)
LIST_DECLARE(AnimationInstance)

// Declare functions
LIST_DECLARE_FUNCTIONS(int)
LIST_DECLARE_FUNCTIONS(float)
LIST_DECLARE_FUNCTIONS(Texture2D)
LIST_DECLARE_FUNCTIONS(AnimationInstance)