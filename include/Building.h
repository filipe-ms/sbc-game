#pragma once
#include <Drawable.h>
#include <BuildingMetadata.h>

typedef enum Building_Type {
	BUILDING_TYPE_TOWN_HALL = 0,
	BUILDING_TYPE_BARBARIAN_TRAINING_TENT,
	BUILDING_TYPE_MARKETPLACE,
	BUILDING_TYPE_HOUSE,
} Building_Type;

typedef struct Building {
	Vector2* Position;
	Drawable Drawable;
	BuildingMetadata* Metadata;
} Building;

void Building_Init(Building* building, Building_Type type);
void Building_Update(Building* building);
void Building_Draw(Building* building);