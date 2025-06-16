#include "Building.h"
#include "DrawableMetadata.h"
#include <BuildingMetadata.h>

void Building_Init(Building* building, Building_Type type)
{
	building->Position = &building->Drawable.Position;
	building->Metadata = BuildingMetadata_GetBuildingMetadataByType(type);
	building->Drawable = building->Metadata->Drawable;
}

void Building_Update(Building* building)
{
}

void Building_Draw(Building* building)
{
	Drawable_Draw(&building->Drawable);

	Rectangle destination = Drawable_CalculateDestination(&building->Drawable);
	destination.x = building->Position->x - building->Drawable.Offset.x;
	destination.y = building->Position->y - building->Drawable.Offset.y;
	DrawRectangleLinesEx(destination, 5, RED);
}

