// File: Buttons.h
#pragma once

#include "raylib.h"
#include "Function.h"

typedef struct MenuButton {
    Rectangle Bounds;
    char* Text;
    int FontSize;
    Color Color;
    Color HoverColor;
} MenuButton;

void Button_Draw(MenuButton* button);

typedef struct TransparentButton {
    Rectangle Bounds;
    Function_Arg1 Function;
    bool IsUsingGameCamera;
    bool IsPressed;
    bool IsActive;
    Function_Arg1 OnHover;
    Function_Arg1 OnClick;
} TransparentButton;

void TransparentButton_Init(TransparentButton* button, Function_Arg1 onClick, bool isUsingGameCamera);
void TransparentButton_InitHover(TransparentButton* button, Function_Arg1 onClick, Function_Arg1 onHover, bool isUsingGameCamera);
void TransparentButton_Update(TransparentButton* button);