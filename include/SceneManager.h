// SCENE_MANAGER_H
#pragma once

#include "raylib.h"
#include <Function.h>

typedef Function Scene_Function;

typedef enum SceneReference {
    SCENEREFERENCE_NONE = -1,
    SCENEREFERENCE_EXIT,
    SCENEREFERENCE_MAIN_MENU,
    SCENEREFERENCE_GAME,
    SCENEREFERENCE_CREDITS,
    SCENEREFERENCE_YOU_WON,
    SCENEREFERENCE_YOU_LOST,
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