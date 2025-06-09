#include <raylib.h>
#include <Drawable.h>

Drawable Drawable_Build(Texture2D* texture, Rectangle source, Rectangle destination, Vector2 offset, float rotation, Color color)
{
    Drawable drawable;
    drawable.Texture = texture;
    drawable.Source = source;
    drawable.Destination = destination;
    drawable.Offset = offset;
    drawable.Rotation = rotation;
    drawable.Color = color;
    return drawable;
}

void Drawable_Draw(Drawable* drawable) {
    DrawTexturePro(
        *drawable->Texture,
        drawable->Source,
        drawable->Destination,
        drawable->Offset,
        drawable->Rotation,
        drawable->Color);
}