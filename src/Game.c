// File: Game.c
#include "Game.h"

#include "GameMap.h"
#include "Unit.h"
#include "AnimationMetadata.h"
#include "GameUnit.h"
#include "GameCamera.h"
#include "GameUI.h"

// DEBUG UNIT
GameUnit gameUnit;

void Game_Init(void) {
	AnimationMetadata_Load();

	GameMap_Init();
	GameCamera_Init();
	GameUnit_Init(&gameUnit, BARBARIAN);
}

void Game_Update(void) {
	Map_Update();

	GameUnit_Update(&gameUnit);
	GameCamera_Update();
}

void Game_Draw(void) {
	BeginDrawing();
	ClearBackground(BLACK);
	
	BeginMode2D(GameCamera);
	{	// Elementos do jogo sensíveis à posição da câmera
		Map_Draw();
		GameUnit_Draw(&gameUnit);
	}
	EndMode2D();

	GameUI_Update();
	
    EndDrawing();
}

void Game_Unload(void) {
	AnimationMetadata_Unload();

	GameMap_Unload();
}