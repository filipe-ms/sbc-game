// File: Buttons.h
#pragma once

#include "raylib.h"
#include "Function.h"
#include "Drawable.h"

typedef struct MenuButton {
    Rectangle Bounds;
    char* Text;
    int FontSize;
    Color Color;
    Color HoverColor;
} MenuButton;

void Button_Draw(MenuButton* button);

#pragma region TransparentButton
typedef struct TransparentButton {
    Vector2* Position;

    Rectangle Bounds;
    Function_Arg1 Function;
    bool IsUsingGameCamera;
    bool IsPressed;
    bool IsActive;
    bool IsHovered;

    void* Owner;

    Function_Arg1 OnHoverBegin;
    Function_Arg1 OnHoverEnd;
    Function_Arg1 OnClick;
} TransparentButton;

void TransparentButton_Init(
    TransparentButton* button,
    void* owner,
    bool isUsingGameCamera);

void TransparentButton_AddClickEvents(
    TransparentButton* button,
    Function_Arg1 onClick);

void TransparentButton_AddHoverEvents(
    TransparentButton* button,
    Function_Arg1 onHoverBegin,
    Function_Arg1 onHoverEnd);

void TransparentButton_Update(TransparentButton* button);
#pragma endregion

typedef struct DrawableButton {
    TransparentButton TransparentButton;
    Drawable Drawable;
} DrawableButton;

void DrawableButton_Init(
    DrawableButton* button,
    void* owner,
    bool isUsingGameCamera,
    Drawable drawable);

void DrawableButton_AddClickEvents(
    DrawableButton* button,
    Function_Arg1 onClick
);

void DrawableButton_AddHoverEvents(
    DrawableButton* button,
    Function_Arg1 onHoverBegin,
    Function_Arg1 onHoverEnd
);

void DrawableButton_Update(DrawableButton* button);
void DrawableButton_Draw(DrawableButton* button);