// CAMERA_H

#pragma once

#include "raylib.h"

#define GAMECAMERA_SCROLL_SPEED 2500.0f

extern Camera2D GameCamera;

void GameCamera_Init(void);
void GameCamera_Update(void);