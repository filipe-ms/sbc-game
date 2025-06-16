// File: GameCamera.c
#include "GameCamera.h"

#include "Constants.h"

#include "raylib.h"

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

static inline float GetCameraMaxX(void) { return (float)(CONSTANTS_MAP_WIDTH * CONSTANTS_TILE_SIZE_F) - GetScreenWidth(); }
static inline float GetCameraMaxY(void) { return (float)(CONSTANTS_MAP_HEIGHT * CONSTANTS_TILE_SIZE_F) - GetScreenHeight(); }

void GameCamera_Update(void) {

	float displacement = GAMECAMERA_SCROLL_SPEED * GetFrameTime();
	
	float update_x = GameCamera.target.x;
	float update_y = GameCamera.target.y;

	// Scroll com teclado
	if (IsKeyDown(KEY_W)) update_y -= displacement;
	if (IsKeyDown(KEY_A)) update_x -= displacement;
	if (IsKeyDown(KEY_S)) update_y += displacement;
	if (IsKeyDown(KEY_D)) update_x += displacement;

	if (update_x >= 0 && update_x <= GetCameraMaxX()) GameCamera.target.x = update_x;
	if (update_y >= 0 && update_y <= GetCameraMaxY()) GameCamera.target.y = update_y;
}