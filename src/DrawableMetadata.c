#include "DrawableMetadata.h"
#include "Building.h"
#include "raylib.h"
#include "Constants.h"
#include <BuildingMetadata.h>

BuildingMetadata Metadata[4];

static Texture2D town_hall_texture;
static Texture2D barbarian_training_tent;
static Texture2D marketplace_texture;
static Texture2D house_texture;

BuildingMetadata* BuildingMetadata_GetBuildingMetadataByType(Building_Type type)
{
	return &Metadata[type];
}

static BuildingMetadata CreateBuildingMetadata(Texture2D* texture, int occupancyTileWidth, int occupancyTileHeight, int centerTileX, int centerTileY) {
	Rectangle source = (Rectangle){ 0, 0, texture->width, texture->height };
	Vector2 position = (Vector2){ 0 };

	float width = CONSTANTS_TILE_SIZE * occupancyTileWidth;
	float height = CONSTANTS_TILE_SIZE * occupancyTileHeight;

	Vector2 scale = (Vector2){ width / texture->width, height / texture->height };

	Vector2 offset = (Vector2){ CONSTANTS_TILE_SIZE * centerTileX + CONSTANTS_TILE_SIZE / 2, CONSTANTS_TILE_SIZE * centerTileY + CONSTANTS_TILE_SIZE / 2 };

	BuildingMetadata metadata = BuildingMetadata_Build(5, 4, centerTileX, centerTileY, Drawable_Build(texture, source, position, scale, offset, 0.0f, WHITE));
	return metadata;
}

void BuildingMetadata_Load(void)
{
	town_hall_texture = LoadTexture("buildings/town_hall.png");
	barbarian_training_tent = LoadTexture("buildings/barbarian_training_tent.png");
	marketplace_texture = LoadTexture("buildings/marketplace.png");
	house_texture = LoadTexture("buildings/house.png");

	Metadata[BUILDING_TYPE_TOWN_HALL] = CreateBuildingMetadata(&town_hall_texture, 5, 4, 2, 3);
	Metadata[BUILDING_TYPE_BARBARIAN_TRAINING_TENT] = CreateBuildingMetadata(&barbarian_training_tent, 3, 3, 1, 2);
	Metadata[BUILDING_TYPE_MARKETPLACE] = CreateBuildingMetadata(&marketplace_texture, 3, 3, 1, 2);
	Metadata[BUILDING_TYPE_HOUSE] = CreateBuildingMetadata(&house_texture, 2, 2, 0, 1);
}

void BuildingMetadata_Unload(void)
{
	UnloadTexture(town_hall_texture);
	UnloadTexture(barbarian_training_tent);
	UnloadTexture(marketplace_texture);
	UnloadTexture(house_texture);
}