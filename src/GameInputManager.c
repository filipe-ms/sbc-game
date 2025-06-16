// File: GameInputManager.c
#include "GameInputManager.h"
#include "Constants.h"
#include "GameCamera.h"

#include "raylib.h"

Vector2 GameInputManager_GetMouseToWorld2D() {
	Vector2 mousePos = GetMousePosition();
	Vector2 worldPos = GetScreenToWorld2D(mousePos, GameCamera);
	return worldPos;
}

Vector2 GameInputManager_ConvertToGridSnapInputCoordinate(Vector2 position) {
	float half_tile_size = CONSTANTS_TILE_SIZE_F / 2.0f;
	Vector2 snappedPosition = (Vector2){
		(int)((position.x) / CONSTANTS_TILE_SIZE_F),
		(int)((position.y) / CONSTANTS_TILE_SIZE_F)
	};
	Vector2 gridPosition = (Vector2){ CONSTANTS_TILE_SIZE_F * snappedPosition.x + half_tile_size, CONSTANTS_TILE_SIZE_F * snappedPosition.y + half_tile_size };
	return gridPosition;
}

bool GameInputManager_IsMouseIntersectingWith(Rectangle world2dRectangle) {
	Vector2 worldPos = GameInputManager_GetMouseToWorld2D();
	return CheckCollisionPointRec(worldPos, world2dRectangle);
}