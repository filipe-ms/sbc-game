// File: GameCamera.c
#include "GameCamera.h"

#include "GameMap.h"
#include "Constants.h"

#include "raylib.h"
#include "raymath.h"

Camera2D GameCamera;

void GameCamera_Init(void)
{
	Vector2 offset = { 0 };
	float zoom = 1.0f;

	GameCamera = (Camera2D){
		.offset = offset,
		.target = { 0 },
		.rotation = 0.0f,
		.zoom = zoom
	};
}

static inline float GetCameraMaxX(void) { return (float)(MAP_WIDTH * CONSTANTS_TILE_SIZE_F) - GetScreenWidth(); }
static inline float GetCameraMaxY(void) { return (float)(MAP_HEIGHT * CONSTANTS_TILE_SIZE_F) - GetScreenHeight(); }

void GameCamera_Update(void) {

	float displacement = GAMECAMERA_SCROLL_SPEED * GetFrameTime();
	
	float update_x = GameCamera.target.x;
	float update_y = GameCamera.target.y;

	// Scroll com teclado
	if (IsKeyDown(KEY_W)) update_y -= displacement;
	if (IsKeyDown(KEY_A)) update_x -= displacement;
	if (IsKeyDown(KEY_S)) update_y += displacement;
	if (IsKeyDown(KEY_D)) update_x += displacement;

	GameCamera.target.x = Clamp(update_x, 0, GetCameraMaxX());
	GameCamera.target.y = Clamp(update_y, 0, GetCameraMaxY());
}