#pragma once
#include <Drawable.h>

typedef struct BuildingMetadata {
	int OccupancyTileWidth;
	int OccupancyTileHeight;
	int CenterTileX;
	int CenterTileY;

	Drawable Drawable;
} BuildingMetadata;

BuildingMetadata BuildingMetadata_Build(int occupancyTileWidth, int occupancyTileHeight, int centerTileX, int centerTileY, Drawable drawable);