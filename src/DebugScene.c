// File: DebugScene.c

#include <Button.h>
#include "DebugScene.h"
#include "raylib.h";

Texture2D buttonTex;
DrawableButton button;

static void OnClick(DrawableButton* owner) {
    TraceLog(LOG_INFO, "Click!");
}

void DebugScene_Init(void)
{
    buttonTex = LoadTexture("ui/Blood.png");

    Rectangle rec = (Rectangle){
        .x = 0,
        .y = 0,
        .width = buttonTex.width,
        .height = buttonTex.height
    };

    DrawableButton_Init(&button, &button, false, Drawable_Build(&buttonTex, rec, (Vector2) { 0 }, (Vector2) { 1, 1 }, (Vector2) { 0 }, 0.0f, WHITE));
    DrawableButton_AddClickEvents(&button, OnClick);
}

void DebugScene_Unload(void)
{
}

void DebugScene_Update(void)
{
    DrawableButton_Update(&button);
}

void DebugScene_Draw(void)
{
    BeginDrawing();
    ClearBackground(BLACK);
   
    DrawableButton_Draw(&button);

    EndDrawing();
}