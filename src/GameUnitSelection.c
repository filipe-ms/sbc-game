// File: GameUnitSelection.c
#include "GameUnitSelection.h"

#include "GameCamera.h"

GameUnit* SelectedUnit = NULL;

// Includes provisórios, remover eventualmente

#include "Game.h" // Assim que as unidades virarem lista e tal, fazer isso sumir

static Rectangle GetGameUnitRectangle(GameUnit* unit) {
	if (!unit || !unit->Unit.Position) return (Rectangle) { 0, 0, 0, 0 };
	return (Rectangle) {
		unit->Unit.Animation.Drawable.Position.x,
			unit->Unit.Animation.Drawable.Position.y,
			unit->Unit.Animation.Drawable.Scale.x* unit->Unit.Animation.Drawable.Source.width,
			unit->Unit.Animation.Drawable.Scale.y* unit->Unit.Animation.Drawable.Source.height
	};
}
static void DrawSelectionBox(GameUnit* unit) {
	Rectangle rect =
		(Rectangle){
			unit->Unit.Animation.Drawable.Position.x,
			unit->Unit.Animation.Drawable.Position.y,
			unit->Unit.Animation.Drawable.Scale.x * unit->Unit.Animation.Drawable.Source.width,
			unit->Unit.Animation.Drawable.Scale.y * unit->Unit.Animation.Drawable.Source.height
	};
	DrawRectangleLinesEx(rect, 5.0f, RED);
}
static Vector2 GetMouseToWorld2D() {
	Vector2 mousePos = GetMousePosition();
	return GetScreenToWorld2D(mousePos, GameCamera);
}

void GameUnitSelection_Update(void) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (CheckCollisionPointRec(GetMouseToWorld2D(), GetGameUnitRectangle(&gameUnit))) {
            SelectedUnit = &gameUnit;
        }
        else {
            SelectedUnit = NULL;
        }
    }
}
void GameUnitSelection_Draw(void) {
	if (SelectedUnit) {
		DrawSelectionBox(SelectedUnit);
	}
}