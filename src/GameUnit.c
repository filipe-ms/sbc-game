// GAMEUNIT_C

#include "GameUnit.h"

#include "raylib.h"

#include "UnitMetadata.h"
#include "GameInputManager.h"

void DrawSelectionHint(GameUnit* unit) {
    Rectangle rect =
        (Rectangle){
            unit->Unit.Animation.Drawable.Position.x,
            unit->Unit.Animation.Drawable.Position.y,
            unit->Unit.Animation.Drawable.Scale.x * unit->Unit.Animation.Drawable.Source.width,
            unit->Unit.Animation.Drawable.Scale.y * unit->Unit.Animation.Drawable.Source.height
    };
    DrawRectangleLinesEx(rect, 5.0f, RED);
}

Rectangle BuildIntersectionArea(GameUnit* unit) {
    Rectangle rect =
        (Rectangle){
            unit->Unit.Animation.Drawable.Position.x,
            unit->Unit.Animation.Drawable.Position.y,
            unit->Unit.Animation.Drawable.Scale.x * unit->Unit.Animation.Drawable.Source.width,
            unit->Unit.Animation.Drawable.Scale.y * unit->Unit.Animation.Drawable.Source.height
    };
    return rect;
}

void GameUnit_Init(GameUnit* unit, Unit_Type type) {
    Unit_Init(&unit->Unit, type);
}

void GameUnit_Update(GameUnit* unit) {
    Rectangle interactionRectangle = BuildIntersectionArea(unit);
        
    unit->IsBeingHovered = GameInputManager_IsMouseIntersectingWith(interactionRectangle);

    if (IsKeyPressed(KEY_W)) {
        Unit_ChangeDirection(&unit->Unit, 3);
    }
    else if (IsKeyPressed(KEY_A)) {
        Unit_ChangeDirection(&unit->Unit, 1);
    }
    else if (IsKeyPressed(KEY_S)) {
        Unit_ChangeDirection(&unit->Unit, 0);
    }
    else if (IsKeyPressed(KEY_D)) {
        Unit_ChangeDirection(&unit->Unit, 2);
    }

    Unit_Update(&unit->Unit);
}

void GameUnit_Draw(GameUnit* unit)
{
    Unit_Draw(&unit->Unit);

    //DrawSelectionHint(unit);
    if (unit->IsBeingHovered) {
        DrawSelectionHint(unit);
    }
}
