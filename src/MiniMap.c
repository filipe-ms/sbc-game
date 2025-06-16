// File: MiniMap.c
#include "MiniMap.h"

#include "GameMap.h"
#include "GameCamera.h"
#include "Constants.h"

#include "raymath.h"

MiniMap Minimap; // Extern.

Vector2 MinimapScale;
Rectangle MinimapInnerRectangle;

Rectangle upperBorder;
Rectangle lowerBorder;
Rectangle leftBorder;
Rectangle rightBorder;

int IsDragging = 0;

static Vector2 CalcMinimapScale() {
	Vector2 result;
	result.x = (Minimap.Size.x - 2 * Minimap.BorderSize) / MAP_WIDTH;
	result.y = (Minimap.Size.y - 2 * Minimap.BorderSize) / MAP_HEIGHT;
	return result;
}

static Rectangle CalcMinimapInnerRectangle() {
	return (Rectangle) {
		Minimap.Postition.x + Minimap.BorderSize,
			Minimap.Postition.y + Minimap.BorderSize,
			Minimap.Size.x - 2 * Minimap.BorderSize,
			Minimap.Size.y - 2 * Minimap.BorderSize
	};
}

static Rectangle GetPlayerViewRectangle() {

	Vector2 cameraSizeInTiles = (Vector2){
		CONSTANTS_VIDEO_SETTINGS_WIDTH_BUFFER / CONSTANTS_TILE_SIZE_F,
		CONSTANTS_VIDEO_SETTINGS_HEIGHT_BUFFER / CONSTANTS_TILE_SIZE_F
	};

	Vector2 cameraPosInTiles = {
		GameCamera.target.x / CONSTANTS_TILE_SIZE_F,
		GameCamera.target.y / CONSTANTS_TILE_SIZE_F
	};

	Rectangle rec = {
		Minimap.Postition.x + Minimap.BorderSize + (cameraPosInTiles.x * MinimapScale.x),
		Minimap.Postition.y + Minimap.BorderSize + (cameraPosInTiles.y * MinimapScale.y),
		cameraSizeInTiles.x * MinimapScale.x,
		cameraSizeInTiles.y * MinimapScale.y
	};

	return rec;
}

void MiniMap_Init(Vector2 position, Vector2 size, float borderSize, float zoom, Color borderColor, Color backgroundColor) {
	Minimap.Postition = position;
	Minimap.BorderSize = borderSize;
	Minimap.Size = size;
	Minimap.Zoom = zoom;
	Minimap.BorderColor = borderColor;
	Minimap.BackgroundColor = backgroundColor;

	MinimapInnerRectangle = CalcMinimapInnerRectangle();
	MinimapScale = CalcMinimapScale();

	upperBorder = (Rectangle){ Minimap.Postition.x, Minimap.Postition.y, Minimap.Size.x, Minimap.BorderSize };
	lowerBorder = (Rectangle){ Minimap.Postition.x, Minimap.Postition.y + Minimap.Size.y - Minimap.BorderSize, Minimap.Size.x, Minimap.BorderSize };
	leftBorder = (Rectangle){ Minimap.Postition.x, Minimap.Postition.y + Minimap.BorderSize, Minimap.BorderSize, Minimap.Size.y - 2 * Minimap.BorderSize };
	rightBorder = (Rectangle){ Minimap.Postition.x + Minimap.Size.x - Minimap.BorderSize, Minimap.Postition.y + Minimap.BorderSize, Minimap.BorderSize, Minimap.Size.y - 2 * Minimap.BorderSize };
}

static Vector2 DrawUnitInMinimap(Vector2 position) {

	Rectangle rec = { 
		Minimap.Postition.x + Minimap.BorderSize + position.x * MinimapScale.x,
		Minimap.Postition.y + Minimap.BorderSize + position.y * MinimapScale.y,
		MinimapScale.x,
		MinimapScale.y 
	};

	Color color = RED;

	DrawRectangleRec(rec, color);
}

void MiniMap_Update(void) {
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
		Vector2 mousePos = GetMousePosition();

		if (CheckCollisionPointRec(mousePos, MinimapInnerRectangle) || IsDragging) {
			IsDragging = 1;
			Vector2 relativeMousePos = {
				mousePos.x - MinimapInnerRectangle.x,
				mousePos.y - MinimapInnerRectangle.y
			};

			Vector2 targetPosInTiles = {
				relativeMousePos.x / MinimapScale.x,
				relativeMousePos.y / MinimapScale.y
			};

			Vector2 targetPosInWorld = {
				targetPosInTiles.x * CONSTANTS_TILE_SIZE_F,
				targetPosInTiles.y * CONSTANTS_TILE_SIZE_F
			};

			float newCameraX = targetPosInWorld.x - (CONSTANTS_VIDEO_SETTINGS_WIDTH_BUFFER / 2.0f);
			float newCameraY = targetPosInWorld.y - (CONSTANTS_VIDEO_SETTINGS_HEIGHT_BUFFER / 2.0f);

			float maxCamX = (float)(MAP_WIDTH * CONSTANTS_TILE_SIZE_F) - CONSTANTS_VIDEO_SETTINGS_WIDTH_BUFFER;
			float maxCamY = (float)(MAP_HEIGHT * CONSTANTS_TILE_SIZE_F) - CONSTANTS_VIDEO_SETTINGS_HEIGHT_BUFFER;

			GameCamera.target.x = Clamp(newCameraX, 0.0f, maxCamX);
			GameCamera.target.y = Clamp(newCameraY, 0.0f, maxCamY);
		}
	}
	else {
		IsDragging = 0;
	}
}

void MiniMap_Draw(void) {
	DrawRectangleRec(upperBorder, Minimap.BorderColor);
	DrawRectangleRec(lowerBorder, Minimap.BorderColor);
	DrawRectangleRec(leftBorder, Minimap.BorderColor);
	DrawRectangleRec(rightBorder, Minimap.BorderColor);
	DrawRectangleRec(MinimapInnerRectangle, Minimap.BackgroundColor);

	DrawRectangleLinesEx(GetPlayerViewRectangle(), 2.0f, Fade(DARKPURPLE, 0.5f));

	// TODO: Trocar por um loop no mapa para fazer o desenho das unidades no minimap.
	Vector2 unitSim = { 0, 0 };
	DrawUnitInMinimap(unitSim);
}