// File: DebugScene.c
#include "DebugScene.h"

#include "AnimationMetadata.h"
#include "GameUnit.h"
#include "Unit.h"
#include <Expression.h>
#include "Button.h"

#include "raylib.h"

Texture2D buttonTex;
DrawableButton button;

AnimatedButton button2;

GameUnit gameUnit;

Expression expression;

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
    AnimationMetadata_Load();

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

    GameUnit_Init(&gameUnit, BARBARIAN);
    Unit_ChangeAction(&gameUnit.Unit, GAMEUNIT_ACTION_ATTACK);
    
    // Position
    *gameUnit.Position = (Vector2){ 150, 100 };
    gameUnit.Unit.Animation.Order = ANIMATION_ORDER_FORWARD_AND_BACK;

    Expression_Init(&expression, EXPRESSION_CURIOUS);
    *expression.Position = (Vector2){ 200, 100 };
}

void DebugScene_Unload(void)
{
}

void DebugScene_Update(void)
{
    DrawableButton_Update(&button);
    AnimatedButton_Update(&button2);

    GameUnit_Update(&gameUnit);
    Expression_Update(&expression);

    if (IsKeyPressed(KEY_A)) {
        Expression_Change(&expression, (Expression_Type)((expression.Type + 1) % 8));
    }
}

void DebugScene_Draw(void)
{
    BeginDrawing();
    ClearBackground(BLACK);
   
    DrawableButton_Draw(&button);
    AnimatedButton_Draw(&button2);

    GameUnit_Draw(&gameUnit);
    Expression_Draw(&expression);

    EndDrawing();
}