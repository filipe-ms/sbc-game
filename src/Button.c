// File: Buttons.c
#include "Button.h"
#include "Function.h"
#include "raylib.h"

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

void TransparentButton_Init(TransparentButton* button, Function_Arg1 onClick, bool isUsingGameCamera) {
    button->OnClick = onClick;
    button->IsUsingGameCamera = isUsingGameCamera;
}
void TransparentButton_InitHover(TransparentButton* button, Function_Arg1 onClick, Function_Arg1 onHover, bool isUsingGameCamera) {
    TransparentButton_Init(button, onClick, isUsingGameCamera);
    button->OnHover = onHover;
}
void TransparentButton_Update(TransparentButton* button);