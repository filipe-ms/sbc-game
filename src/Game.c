#include "Map.h"

void Game_Init(void) {
	Map_Init();
}

void Game_Update(void) {
	Map_Update();
}

void Game_Draw(void) {
    BeginDrawing();
    ClearBackground(BLACK);
	Map_Draw();
    EndDrawing();
}

void Game_Unload(void) {
	Map_Unload();
}