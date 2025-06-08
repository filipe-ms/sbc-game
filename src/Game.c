#include "Map.h"
#include "Unit.h"

Unit unit;

void Game_Init(void) {
	Map_Init();
	Unit_Load();
	Unit_Init(&unit);
}

void Game_Update(void) {
	Map_Update();
}

void Game_Draw(void) {
    BeginDrawing();
    ClearBackground(BLACK);

	Map_Draw();
	Unit_Draw(&unit);

    EndDrawing();
}

void Game_Unload(void) {
	Map_Unload();
	Unit_Unload();
}