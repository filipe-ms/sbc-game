#include "Map.h"
#include "Unit.h"
#include "UnitMetadata.h"
#include <GameUnit.h>
#include <Camera.h>

GameUnit gameUnit;

void Game_Init(void) {
	UnitMetadata_Load();

	Map_Init();
	Camera_Init();
	GameUnit_Init(&gameUnit, BARBARIAN);
}

void Game_Update(void) {
	Map_Update();

	GameUnit_Update(&gameUnit);
}

void Game_Draw(void) {
    BeginDrawing();
    ClearBackground(BLACK);

	Map_Draw();
	GameUnit_Draw(&gameUnit);

    EndDrawing();
}

void Game_Unload(void) {
	UnitMetadata_Unload();

	Map_Unload();
}