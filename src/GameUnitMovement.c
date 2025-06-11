// File: GameUnitMovement.c

#include "GameUnitMovement.h"

#include "GameUnit.h"
#include "Constants.h"
#include "GameCamera.h"
#include "GameUI.h"
#include "GameUnitSelection.h"

#include "raylib.h"
#include "raymath.h"

static void SetUnitDestination(GameUnit* unit, Vector2 destination) {
	unit->Destination.x = destination.x * CONSTANTS_TILE_SIZE;
	unit->Destination.y = destination.y * CONSTANTS_TILE_SIZE;
}

void DEBUG_GameUnitMovement_Update(void) {
	GameUnit* unit = SelectedUnit;
	if (!unit) return;

	float movementSpeed = 100.0f;
	float displacement = movementSpeed * GetFrameTime();

	if (unit->Position->x != unit->Destination.x || unit->Position->y != unit->Destination.y) {

		float angle = atan2f(unit->Destination.y - unit->Position->y, unit->Destination.x - unit->Position->x);

		unit->Position->x += cosf(angle) * displacement;
		unit->Position->y += sinf(angle) * displacement;
		
		if (fabsf(unit->Position->x - unit->Destination.x) < 1.0f &&
			fabsf(unit->Position->y - unit->Destination.y) < 1.0f) {
			unit->Position->x = unit->Destination.x;
			unit->Position->y = unit->Destination.y;
		}
	}
}