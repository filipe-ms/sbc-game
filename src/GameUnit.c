#include "GameUnit.h"

GameUnit* SelectedUnit;

void DrawSelectionHint() {
	if (!SelectedUnit || !SelectedUnit->IsClickable) return;
    Rectangle rect =
        (Rectangle){
            SelectedUnit->Unit.Animation.Drawable.Position.x,
            SelectedUnit->Unit.Animation.Drawable.Position.y,
            SelectedUnit->Unit.Animation.Drawable.Scale.x,
            SelectedUnit->Unit.Animation.Drawable.Scale.y
    };
    DrawRectangleLinesEx(rect, 5.0f, RED);
}


GameUnit* GameUnit_GetSelected() {
	return SelectedUnit;
}


void UpdateGameUnit() {
    DrawSelectionHint();
}