// GAMEUNIT_C

#include "GameUnit.h"

#include "UnitMetadata.h"
#include "GameInputManager.h"
#include "GameUnitMovement.h"
#include "GameUnitSelection.h"

#include "raylib.h"

static Rectangle GetUnitBox(GameUnit* unit) {
    Rectangle rect =
        (Rectangle){
            unit->Unit.Animation.Drawable.Position.x,
            unit->Unit.Animation.Drawable.Position.y,
            unit->Unit.Animation.Drawable.Scale.x * unit->Unit.Animation.Drawable.Source.width,
            unit->Unit.Animation.Drawable.Scale.y * unit->Unit.Animation.Drawable.Source.height
    };
    return rect;
}

static void DrawHoverHint(GameUnit* unit) {
    Rectangle rect =
        (Rectangle){
            unit->Unit.Animation.Drawable.Position.x,
            unit->Unit.Animation.Drawable.Position.y,
            unit->Unit.Animation.Drawable.Scale.x * unit->Unit.Animation.Drawable.Source.width,
            unit->Unit.Animation.Drawable.Scale.y * unit->Unit.Animation.Drawable.Source.height
    };
    DrawRectangleLinesEx(rect, 5.0f, SKYBLUE);
}

void GameUnit_Init(GameUnit* unit, Unit_Type type) {
    Unit_Init(&unit->Unit, type);
	unit->Position = &unit->Unit.Animation.Drawable.Position;
}

void GameUnit_Update(GameUnit* unit) {
    Rectangle interactionRectangle = GetUnitBox(unit);
        
    unit->IsBeingHovered = GameInputManager_IsMouseIntersectingWith(interactionRectangle);

    if (IsKeyPressed(KEY_W)) Unit_ChangeDirection(&unit->Unit, 3);
    else if (IsKeyPressed(KEY_A)) Unit_ChangeDirection(&unit->Unit, 1);
    else if (IsKeyPressed(KEY_S)) Unit_ChangeDirection(&unit->Unit, 0);
    else if (IsKeyPressed(KEY_D)) Unit_ChangeDirection(&unit->Unit, 2);

    Unit_Update(&unit->Unit);
    DEBUG_GameUnitMovement_Update();

    GameUnitSelection_Update();
}

void GameUnit_Draw(GameUnit* unit)
{
    Unit_Draw(&unit->Unit);

    DrawHoverHint(unit);
    if (unit->IsBeingHovered) {
        DrawHoverHint(unit);
    }

    GameUnitSelection_Draw();
}
