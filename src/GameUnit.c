#include "GameUnit.h"
#include <UnitMetadata.h>

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

void GameUnit_Init(GameUnit* game_unit) {
    Unit_Init(&game_unit->Unit, BARBARIAN);
}

void GameUnit_Load(GameUnit* game_unit)
{
}

void GameUnit_Update(GameUnit* game_unit)
{
}

void GameUnit_Draw(GameUnit* game_unit)
{
}
