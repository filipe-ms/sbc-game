// GAMEINPUTMANAGER_C

#include "GameInputManager.h"

#include "GameCamera.h"

#include "raylib.h"

bool GameInputManager_IsMouseIntersectingWith(Rectangle world2dRectangle) {
	Vector2 mousePos = GetMousePosition();
	Vector2 worldMousePos = GetScreenToWorld2D(mousePos, GameCamera);
	return CheckCollisionPointRec(worldMousePos, world2dRectangle);
}