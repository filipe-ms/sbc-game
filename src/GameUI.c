// File: GameUI.c
#include "GameUI.h"

#include "Constants.h"

#include "MiniMap.h"
#include "GameCamera.h"

Rectangle aboveMinimap;
Rectangle belowMinimap;

void GameUI_Init(void) {
	
	// Inicializa o minimapa
	Vector2 minimapPosition = { 
		CONSTANTS_VIDEO_SETTINGS_WIDTH_BUFFER * 0.8, 
		CONSTANTS_VIDEO_SETTINGS_HEIGHT_BUFFER * 0.1 
	};
	Vector2 minimapSize = { 
		CONSTANTS_VIDEO_SETTINGS_WIDTH_BUFFER * 0.2,
		CONSTANTS_VIDEO_SETTINGS_WIDTH_BUFFER * 0.2
	};
	float minimapBorderSize = 5.0f;
	float minimapZoom = 1.0f; // Não implementado
	Color minimapBorderColor = Fade(BLUE, 0.5f);
	Color minimapBackgroundColor = Fade(BLACK, 0.2f);

	MiniMap_Init(minimapPosition, minimapSize, minimapBorderSize, minimapZoom, minimapBorderColor, minimapBackgroundColor);

	// Inicializa o resto da UI
	aboveMinimap = (Rectangle){ minimapPosition.x, 0, CONSTANTS_VIDEO_SETTINGS_WIDTH_BUFFER - minimapSize.x, minimapPosition.y };
	belowMinimap = (Rectangle){ minimapPosition.x, minimapPosition.y + minimapSize.y, CONSTANTS_VIDEO_SETTINGS_WIDTH_BUFFER - minimapSize.x, CONSTANTS_VIDEO_SETTINGS_HEIGHT_BUFFER - (minimapPosition.y + minimapSize.y) };
}


static void DrawGameUI() {
	DrawRectangleRec(aboveMinimap, Fade(BLACK, 0.5f));
	DrawRectangleRec(belowMinimap, Fade(BLACK, 0.5f));
}


void GameUI_Update(void) {
	MiniMap_Update();
}
void GameUI_Draw(void) {
	DrawGameUI();
	MiniMap_Draw();

}
void GameUI_Unload(void) {}