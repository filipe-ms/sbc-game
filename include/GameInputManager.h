// File: GameInputManager.h
#pragma once

#include "raylib.h"

Vector2 GameInputManager_GetMouseToWorld2D(void);
bool GameInputManager_IsMouseIntersectingWith(Rectangle world2dRectangle);