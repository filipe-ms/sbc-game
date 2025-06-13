// File: DebugScene.c

#include <Button.h>
#include "DebugScene.h"
#include "raylib.h";
#include "UnitMetadata.h"

Texture2D buttonTex;
DrawableButton button;

AnimatedButton button2;

static void OnClick(DrawableButton* owner) {
    TraceLog(LOG_INFO, "Click!");
}

static void OnHoverBegin(DrawableButton* owner) {
    TraceLog(LOG_INFO, "OnHoverBegin!");
}

static void OnHoverEnd(DrawableButton* owner) {
    TraceLog(LOG_INFO, "OnHoverEnd!");
}


void DebugScene_Init(void)
{
    UnitMetadata_Load();

    buttonTex = LoadTexture("ui/Blood.png");

    Rectangle rec = (Rectangle){
        .x = 0,
        .y = 0,
        .width = buttonTex.width,
        .height = buttonTex.height
    };

    DrawableButton_Init(&button, &button, false, Drawable_Build(&buttonTex, rec, (Vector2) { 0 }, (Vector2) { 1, 1 }, (Vector2) { 0 }, 0.0f, WHITE));
    DrawableButton_AddClickEvents(&button, OnClick);

    AnimatedButton_Init(&button2, &button2, false, ANIMATEDBUTTON_TYPE_BLOOD);
    AnimatedButton_SetPosition(&button2, (Vector2) { 100, 100 });

    AnimatedButton_AddClickEvents(&button2, OnClick);
    AnimatedButton_AddHoverEvents(&button2, OnHoverBegin, OnHoverEnd);
}

void DebugScene_Unload(void)
{
}

void DebugScene_Update(void)
{
    DrawableButton_Update(&button);
    AnimatedButton_Update(&button2);
}

void DebugScene_Draw(void)
{
    BeginDrawing();
    ClearBackground(BLACK);
   
    DrawableButton_Draw(&button);
    AnimatedButton_Draw(&button2);

    EndDrawing();
}