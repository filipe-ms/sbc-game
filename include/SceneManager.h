// File: SceneManager.h
#pragma once

#include "Function.h"

#include "raylib.h"

typedef Function Scene_Function;

typedef enum SceneReference {
    SCENEREFERENCE_NONE = -1,
    SCENEREFERENCE_EXIT,
    SCENEREFERENCE_MAIN_MENU,
    SCENEREFERENCE_GAME,
    SCENEREFERENCE_CREDITS,
    SCENEREFERENCE_YOU_WON,
    SCENEREFERENCE_YOU_LOST,

    SCENEREFERENCE_DEBUG,
} SceneReference;

typedef struct Scene {
    SceneReference SceneRef;
    Scene_Function Init;
    Scene_Function Update;
    Scene_Function Draw;
    Scene_Function Unload;
} Scene;

void SceneManager_Init(void);
void SceneManager_ChangeScene(SceneReference scene);
void SceneManager_LoopScene(void);