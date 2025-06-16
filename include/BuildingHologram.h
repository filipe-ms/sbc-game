#pragma once
#include <Building.h>
#include "GameInputManager.h"

typedef struct BuildingHologram {
	Color* Color;
	Vector2* Position;

	float ElapsedTime;

	Building Building;

	bool IsAbleToBuild;
	bool IsActive;
} BuildingHologram;

void BuildingHologram_Init(BuildingHologram* buildingHologram, Building_Type type);
void BuildingHologram_Update(BuildingHologram* buildingHologram);
void BuildingHologram_Draw(BuildingHologram* buildingHologram);