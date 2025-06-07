#include <Button.h>
#include <raylib.h>

void Button_Draw(Button* button) {
    Vector2 textSize = MeasureTextEx(GetFontDefault(), button->text, (float)button->font_size, 5.0f);
    bool is_hovered = CheckCollisionPointRec(GetMousePosition(), button->bounds);

    Vector2 textPosition = {
        button->bounds.x + (button->bounds.width - textSize.x) / 2,
        button->bounds.y + (button->bounds.height - textSize.y) / 2
    };
    DrawRectangleLines((int)button->bounds.x, (int)button->bounds.y, (int)button->bounds.width, (int)button->bounds.height, button->color);

    if (is_hovered) DrawTextEx(GetFontDefault(), button->text, textPosition, (float)button->font_size, 5.0f, button->hover_color);
    else DrawTextEx(GetFontDefault(), button->text, textPosition, (float)button->font_size, 5.0f, button->color);
}