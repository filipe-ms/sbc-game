// File: GameUnit.c
#include "GameUnit.h"

#include "AnimationMetadata.h"
#include "GameInputManager.h"
#include "GameUnitMovement.h"
#include "GameUnitSelection.h"
#include "Button.h"

#include "raylib.h"

static void OnClick(GameUnit* unit) {
    TraceLog(LOG_INFO, "| Click Event: %d |", unit);
}

static void OnHoverBegin(GameUnit* unit) {
    TraceLog(LOG_INFO, "| Hover Begins: %d |", unit);
}

static void OnHoverEnds(GameUnit* unit) {
    TraceLog(LOG_INFO, "| Hover Ends: %d |", unit);
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

static void InitPositionalData(GameUnit* unit) {
	unit->PositionalData.Position = &(*unit->Unit.Position); // Pegando o ponteiro da posição real da unidade.
    unit->PositionalData.FinalDestination = (Vector2){ -1, -1 };
    unit->PositionalData.NextWaypoint = (Vector2){ -1, -1 };
    unit->PositionalData.Path = NULL;
}

void GameUnit_Init(GameUnit* unit, Unit_Type type) {
    Unit_Init(&unit->Unit, type);

	unit->Position = &unit->Unit.Animation.Drawable.Position;

    // Transparent button logic - needs improvement (?)
    TransparentButton_Init(&unit->TransparentButton, &unit, true);
    TransparentButton_AddHoverEvents(&unit->TransparentButton, OnHoverBegin, OnHoverEnds);
    TransparentButton_AddClickEvents(&unit->TransparentButton, OnClick);

	InitPositionalData(unit);
}

void GameUnit_Update(GameUnit* unit) {
    Rectangle playerBounds = GameUnit_CalculateCollisionBounds(unit);
    unit->TransparentButton.Bounds = playerBounds;
    TransparentButton_Update(&unit->TransparentButton);
    
    unit->IsBeingHovered = GameInputManager_IsMouseIntersectingWith(playerBounds);

    if (IsKeyPressed(KEY_W)) Unit_ChangeDirection(&unit->Unit, 3);
    else if (IsKeyPressed(KEY_A)) Unit_ChangeDirection(&unit->Unit, 1);
    else if (IsKeyPressed(KEY_S)) Unit_ChangeDirection(&unit->Unit, 0);
    else if (IsKeyPressed(KEY_D)) Unit_ChangeDirection(&unit->Unit, 2);

    Unit_Update(&unit->Unit);

    GameUnitSelection_Update();

    { // Update de movimento
        GameUnitMovement_Update(SelectedUnit);
    }
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
