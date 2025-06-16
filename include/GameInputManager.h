// File: GameInputManager.h
#pragma once

#include "raylib.h"

Vector2 GameInputManager_GetMouseToWorld2D(void);
Vector2 GameInputManager_ConvertToGridSnapInputCoordinate(Vector2 position);
bool GameInputManager_IsMouseIntersectingWith(Rectangle world2dRectangle);