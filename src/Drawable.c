#include <raylib.h>
#include <Drawable.h>

void Drawable_Draw(Drawable* drawable) {
    DrawTexturePro(
        *drawable->Texture,
        drawable->Source,
        drawable->Destination,
        drawable->Offset,
        drawable->Rotation,
        drawable->Color);
}