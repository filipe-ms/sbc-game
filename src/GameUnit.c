// File: GameUnit.c
#include "GameUnit.h"

#include "UnitMetadata.h"
#include "GameInputManager.h"
#include "GameUnitMovement.h"
#include "GameUnitSelection.h"
#include "Button.h"

#include "raylib.h"

static void OnClick(GameUnit* unit);
static void OnHoverBegin(GameUnit* unit);
static void OnHoverEnds(GameUnit* unit);

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
    TransparentButton_Init(&unit->TransparentButton, &unit, true);
    TransparentButton_AddHoverEvents(&unit->TransparentButton, OnHoverBegin, OnHoverEnds);
    TransparentButton_AddClickEvents(&unit->TransparentButton, OnClick);
}

void OnClick(GameUnit* unit) {
    TraceLog(LOG_INFO, "| Click Event: %d |", unit);
}

void OnHoverBegin(GameUnit* unit) {
    TraceLog(LOG_INFO, "| Hover Begins: %d |", unit);
}

void OnHoverEnds(GameUnit* unit) {
    TraceLog(LOG_INFO, "| Hover Ends: %d |", unit);
}

void GameUnit_Update(GameUnit* unit) {
    unit->TransparentButton.Bounds = GameUnit_CalculateCollisionBounds(unit);

    TransparentButton_Update(&unit->TransparentButton);

    Rectangle interactionRectangle = GameUnit_CalculateCollisionBounds(unit);
        
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

Rectangle GameUnit_CalculateCollisionBounds(GameUnit* unit)
{
    return Drawable_CalculateDestination(&unit->Unit.Animation.Drawable);
}
