// File: GameInputManager.c

#include "GameInputManager.h"

#include "GameCamera.h"

#include "raylib.h"

Vector2 GameInputManager_GetMouseToWorld2D() {
	Vector2 mousePos = GetMousePosition();
	Vector2 worldPos = GetScreenToWorld2D(mousePos, GameCamera);
	return worldPos;
}

bool GameInputManager_IsMouseIntersectingWith(Rectangle world2dRectangle) {
	Vector2 worldPos = GameInputManager_GetMouseToWorld2D();
	return CheckCollisionPointRec(worldPos, world2dRectangle);
}