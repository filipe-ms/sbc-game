// File: Button.c
#include "Button.h"
#include "Function.h"
#include "raylib.h"
#include "GameInputManager.h"
#include <UnitMetadata.h>

void Button_Draw(MenuButton* button) {
    Vector2 TextSize = MeasureTextEx(GetFontDefault(), button->Text, (float)button->FontSize, 5.0f);
    bool is_hovered = CheckCollisionPointRec(GetMousePosition(), button->Bounds);

    Vector2 TextPosition = {
        button->Bounds.x + (button->Bounds.width - TextSize.x) / 2,
        button->Bounds.y + (button->Bounds.height - TextSize.y) / 2
    };
    DrawRectangleLines((int)button->Bounds.x, (int)button->Bounds.y, (int)button->Bounds.width, (int)button->Bounds.height, button->Color);

    if (is_hovered) DrawTextEx(GetFontDefault(), button->Text, TextPosition, (float)button->FontSize, 5.0f, button->HoverColor);
    else DrawTextEx(GetFontDefault(), button->Text, TextPosition, (float)button->FontSize, 5.0f, button->Color);
}

#pragma region TransparentButton
void TransparentButton_Init(TransparentButton* button, void* owner, bool isUsingGameCamera) {
    button->IsUsingGameCamera = isUsingGameCamera;
    button->Owner = owner;
}

void TransparentButton_AddClickEvents(TransparentButton* button, Function_Arg1 onClick) {
    button->OnClick = onClick;
}

void TransparentButton_AddHoverEvents(TransparentButton* button, Function_Arg1 onHoverBegin, Function_Arg1 onHoverEnds) {
    button->OnHoverBegin = onHoverBegin;
    button->OnHoverEnd = onHoverEnds;
}

void TransparentButton_Update(TransparentButton* button) {
    Vector2 relativeMousePos = button->IsUsingGameCamera ?
        GameInputManager_GetMouseToWorld2D() : GetMousePosition();

    bool isBeingHovered = CheckCollisionPointRec(relativeMousePos, button->Bounds);
    bool isMouseDown = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
    bool isMouseBeingClicked = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

    // If Button is being hovered...
    if (isBeingHovered) {
        if (!button->IsHovered) {
            if (button->OnHoverBegin)
                button->OnHoverBegin(button->Owner);
            button->IsHovered = true;
        }

        if (isMouseBeingClicked) {
            if (!button->IsPressed)
                button->IsPressed = true;
        }
        else {

            if (isMouseDown) {
                if (button->IsPressed) {
                    return;
                }
            }
            else {
                if (button->IsPressed) {
                    button->IsPressed = false;
                    button->IsActive = !button->IsActive;
                    if (button->OnClick)
                        button->OnClick(button->Owner);
                    return;
                }
            }
        }
    } else {
        if (!isMouseDown) {
            button->IsPressed = false;
        }

        if (button->IsHovered) {
            button->IsHovered = false;

            if (button->OnHoverEnd)
                button->OnHoverEnd(button->Owner);
        }
    }
}

void TransparentButton_SetPosition(TransparentButton* button, Vector2 newPosition) {
    button->Bounds.x = newPosition.x;
    button->Bounds.y = newPosition.y;
}
#pragma endregion

#pragma region DrawableButton
void DrawableButton_Init(DrawableButton* button, void* owner, bool isUsingGameCamera, Drawable drawable) {
    button->Position = &button->Drawable.Position;
    button->Drawable = drawable;
    button->TransparentButton.Bounds = Drawable_CalculateDestination(&button->Drawable);
    TransparentButton_Init(&button->TransparentButton, owner, isUsingGameCamera);
}

void DrawableButton_AddClickEvents(DrawableButton * button, Function_Arg1 onClick) {
    TransparentButton_AddClickEvents(&button->TransparentButton, onClick);
}

void DrawableButton_AddHoverEvents(DrawableButton* button, Function_Arg1 onHoverBegin, Function_Arg1 onHoverEnds) {
    TransparentButton_AddHoverEvents(&button->TransparentButton, onHoverBegin, onHoverEnds);
}

void DrawableButton_Update(DrawableButton* button) {
    TransparentButton_Update(&button->TransparentButton);
}

void DrawableButton_Draw(DrawableButton* button) {
    Drawable_Draw(&button->Drawable);
}

void DrawableButton_SetPosition(DrawableButton* button, Vector2 newPosition) {
    TransparentButton_SetPosition(&button->TransparentButton, newPosition);
    *button->Position = newPosition;
    
}
#pragma endregion

#pragma region AnimatedButton
void AnimatedButton_Init(AnimatedButton* button, void* owner, bool isUsingGameCamera, AnimatedButton_Type type)
{
    button->Metadata = UnitMetadata_GetMetadataByAnimatedButtonType(ANIMATEDBUTTON_TYPE_BLOOD);
    button->CurrentAnimation = button->Metadata[ANIMATEDBUTTON_ANIMATIONSTATE_NORMAL];
    button->TransparentButton.Bounds = Drawable_CalculateDestination(&button->CurrentAnimation.Drawable);
    button->TransparentButton.IsUsingGameCamera = isUsingGameCamera;
    button->Position = &button->CurrentAnimation.Drawable.Position;

    TransparentButton_Init(&button->TransparentButton, owner, isUsingGameCamera);
}

void AnimatedButton_AddClickEvents(AnimatedButton* button, Function_Arg1 onClick)
{
    button->TransparentButton.OnClick = onClick;
}

void AnimatedButton_AddHoverEvents(AnimatedButton* button, Function_Arg1 onHoverBegin, Function_Arg1 onHoverEnd)
{
    button->TransparentButton.OnHoverBegin = onHoverBegin;
    button->TransparentButton.OnHoverEnd = onHoverEnd;
}

void AnimatedButton_Update(AnimatedButton* button)
{
    TransparentButton_Update(&button->TransparentButton);

    if (button->TransparentButton.IsPressed && button->TransparentButton.IsHovered) {
        Animation_Change(&button->CurrentAnimation, button->Metadata[ANIMATEDBUTTON_ANIMATIONSTATE_PRESSED]);
    }
    else if (button->TransparentButton.IsActive) {
        Animation_Change(&button->CurrentAnimation, button->Metadata[ANIMATEDBUTTON_ANIMATIONSTATE_ACTIVE]);
    }
    else if (button->TransparentButton.IsHovered) {
        Animation_Change(&button->CurrentAnimation, button->Metadata[ANIMATEDBUTTON_ANIMATIONSTATE_HOVERED]);
    }
    else {
        Animation_Change(&button->CurrentAnimation, button->Metadata[ANIMATEDBUTTON_ANIMATIONSTATE_NORMAL]);
    }

    Animation_Update(&button->CurrentAnimation);
}

void AnimatedButton_Draw(AnimatedButton* button)
{
    Animation_Draw(&button->CurrentAnimation);
}

void AnimatedButton_SetPosition(AnimatedButton* button, Vector2 position) {
    TransparentButton_SetPosition(&button->TransparentButton, position);
    *button->Position = position;
}
#pragma endregion