#include <raylib.h>
#include "Camera.h"

Camera2D Camera_InGame;

void Camera_Init()
{
	Vector2 offset = { 0 };
	float zoom = 1.0f;

	Camera_InGame = (Camera2D){
		.offset = offset,
		.target = { 0 },
		.rotation = 0.0f,
		.zoom = zoom
	};
}
