// SceneManager.c

#include "SceneManager.h"
#include "MainMenu.h"
#include <Function.h>

// Menus
Scene scene;
Scene new_scene;

// Forward definitions
static void InitCurrentScene(void);
static void UpdateCurrentScene(void);
static void DrawCurrentScene(void);
static void UnloadScene(Scene scene);
static void CheckAndReplaceExistingScene();

// Public
void SceneManager_Init() {
    scene.SceneRef = SCENEREFERENCE_NONE;
    new_scene.SceneRef = SCENEREFERENCE_NONE;
}

void SceneManager_ChangeScene(SceneReference nextSceneReference) {
    if (nextSceneReference == scene.SceneRef)
        return;

    switch (nextSceneReference) {
    case SCENEREFERENCE_MAIN_MENU:
        new_scene = (Scene){
            .SceneRef = SCENEREFERENCE_MAIN_MENU,
            .Init = MainMenu_Init,
            .Update = MainMenu_Update,
            .Draw = MainMenu_Draw,
            .Unload = MainMenu_Unload
        };
        break;

    case SCENEREFERENCE_CREDITS:
        break;

    case SCENEREFERENCE_GAME:
        //InitGame();
        break;
    }
}

void SceneManager_LoopScene(void) {
    while (!WindowShouldClose() && scene.SceneRef != SCENEREFERENCE_EXIT) {
        UpdateCurrentScene();
        DrawCurrentScene();
        CheckAndReplaceExistingScene();
    }
}

// Private
static void InitCurrentScene(void) {
    if (!scene.Init) return;
    Function_Invoke(scene.Init);
}

static void UpdateCurrentScene(void) {

    if(!scene.Update) return;
    Function_Invoke(scene.Update);
}

static void DrawCurrentScene(void) {
    if(!scene.Draw) return;
    Function_Invoke(scene.Draw);
}

static void UnloadScene(Scene scene) {
    if (!scene.Unload) return;
    Function_Invoke(scene.Unload);
}

static void CheckAndReplaceExistingScene() {
    if (new_scene.SceneRef != scene.SceneRef) {
        UnloadScene(scene);
        scene = new_scene;
        new_scene.SceneRef = SCENEREFERENCE_NONE;
        InitCurrentScene();
    }
}