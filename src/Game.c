#include "Map.h"
#include "Unit.h"
#include "UnitMetadata.h"

Unit unit;

void Game_Init(void) {
	UnitMetadata_Load();

	Map_Init();
	Unit_Load();
	Unit_Init(&unit, BARBARIAN);
}

void Game_Update(void) {
	Map_Update();

	Unit_Update(&unit);
}

void Game_Draw(void) {
    BeginDrawing();
    ClearBackground(BLACK);

	Map_Draw();
	Unit_Draw(&unit);

    EndDrawing();
}

void Game_Unload(void) {
	UnitMetadata_Unload();

	Map_Unload();
	Unit_Unload();
}