// File: Buttons.h
#pragma once

#include "raylib.h"
#include "Function.h"
#include "Drawable.h"
#include <Animation.h>

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

#pragma region DrawableButton
// Not very useful but its there anyway
typedef struct DrawableButton {
    Vector2* Position;

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
void DrawableButton_SetPosition(DrawableButton* button, Vector2 position);
#pragma endregion

#pragma region AnimatedButton

typedef enum AnimatedButton_Type {
    ANIMATEDBUTTON_TYPE_BLOOD,
} AnimatedButton_Type;

typedef enum AnimatedButton_AnimationState {
    ANIMATEDBUTTON_ANIMATIONSTATE_NORMAL,
    ANIMATEDBUTTON_ANIMATIONSTATE_HOVERED,
    ANIMATEDBUTTON_ANIMATIONSTATE_PRESSED,
    ANIMATEDBUTTON_ANIMATIONSTATE_ACTIVE,
} AnimatedButton_AnimationState;

// Not very useful but its there anyway
typedef struct AnimatedButton {
    Vector2* Position;

    TransparentButton TransparentButton;
    Animation CurrentAnimation;
    Animation* Metadata;
} AnimatedButton;

void AnimatedButton_Init(
    AnimatedButton* button,
    void* owner,
    bool isUsingGameCamera,
    AnimatedButton_Type type);

void AnimatedButton_AddClickEvents(
    AnimatedButton* button,
    Function_Arg1 onClick
);

void AnimatedButton_AddHoverEvents(
    AnimatedButton* button,
    Function_Arg1 onHoverBegin,
    Function_Arg1 onHoverEnd
);

void AnimatedButton_Update(AnimatedButton* button);
void AnimatedButton_Draw(AnimatedButton* button);
void AnimatedButton_SetPosition(AnimatedButton* button, Vector2 position);
#pragma endregion