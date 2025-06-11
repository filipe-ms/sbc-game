#pragma once
#include <raylib.h>
#include <Camera.h>
#include <GameInputManager.h>

bool GameInputManager_IsMouseIntersectingWith(Rectangle world2dRectangle) {
	Vector2 mousePos = GetMousePosition();
	Vector2 worldMousePos = GetScreenToWorld2D(mousePos, Camera_InGame);
	return CheckCollisionPointRec(worldMousePos, world2dRectangle);
}