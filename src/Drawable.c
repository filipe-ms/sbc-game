#include "raylib.h"
#include "Drawable.h"

Drawable Drawable_Build(Texture2D* texture, Rectangle source, Vector2 position, Vector2 scale, Vector2 offset, float rotation, Color color)
{
    Drawable drawable;
    drawable.Texture = texture;
    drawable.Source = source;
    drawable.Position = position;
	drawable.Scale = scale;
    drawable.Offset = offset;
    drawable.Rotation = rotation;
    drawable.Color = color;
    return drawable;
}

void Drawable_Draw(Drawable* drawable) {
	Rectangle destination = { drawable->Position.x, drawable->Position.y, drawable->Source.width * drawable->Scale.x, drawable->Source.height * drawable->Scale.y };

    DrawTexturePro(
        *drawable->Texture,
        drawable->Source,
		destination,
        drawable->Offset,
        drawable->Rotation,
        drawable->Color);
}