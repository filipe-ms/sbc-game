#include <BuildingMetadata.h>

BuildingMetadata BuildingMetadata_Build(int occupancyTileWidth, int occupancyTileHeight, int centerTileX, int centerTileY, Drawable drawable)
{
	BuildingMetadata buildingMetadata;
	buildingMetadata.OccupancyTileWidth = occupancyTileWidth;
	buildingMetadata.OccupancyTileHeight = occupancyTileHeight;
	buildingMetadata.CenterTileX = centerTileX;
	buildingMetadata.CenterTileY = centerTileY;
	buildingMetadata.Drawable = drawable;
	return buildingMetadata;
}