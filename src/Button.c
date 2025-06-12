// File: Button.c
#include "Button.h"
#include "Function.h"
#include "raylib.h"
#include "GameInputManager.h"

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

    // If Button is being hovered...
    if (isBeingHovered) {
        if (!button->IsHovered) {
            if (button->OnHoverBegin)
                button->OnHoverBegin(button->Owner);
            button->IsHovered = true;
        }

        bool isMouseBeingClicked = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

        if (isMouseBeingClicked) {
            if (!button->IsPressed)
                button->IsPressed = true;
        }
        else {
            bool isMouseDown = IsMouseButtonDown(MOUSE_BUTTON_LEFT);

            if (isMouseDown) {
                if (button->IsPressed) {
                    return;
                }
            }
            else {
                if (button->IsPressed) {
                    button->IsPressed = false;
                    if (button->OnClick)
                        button->OnClick(button->Owner);
                    return;
                }
            }
        }
    } else {
        if (button->IsHovered) {
            if (button->OnHoverEnd)
                button->OnHoverEnd(button->Owner);
            button->IsHovered = false;
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
    TransparentButton_SetPosition(button, newPosition);
    button->Drawable.Position = newPosition;
}
#pragma endregion

