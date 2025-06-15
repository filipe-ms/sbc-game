// File: TilesetTextures.c
#include "TilesetTextures.h"

#include "Drawable.h"

// Field
Texture2D Field2DTexture;
FieldTexture Field;
Drawable FieldGrassVariants[18];
Drawable CleanGrassVariants[18];
Drawable FieldRockVariants[10];

static Rectangle GetFieldFloorVariantHelper(int variant, int floortype) {
	int offset = 192 * floortype;

	switch (variant) {
	case 0:  return (Rectangle) { 48, 0 + offset, 48, 48 };		// Base tile
	case 1:  return (Rectangle) { 0, 48 + offset, 48, 48 };		// Upper left
	case 2:  return (Rectangle) { 48, 48 + offset, 48, 48 };	// Upper middle
	case 3:  return (Rectangle) { 96, 48 + offset, 48, 48 };	// Upper right
	case 4:  return (Rectangle) { 0, 96 + offset, 48, 48 };		// Middle left
	case 5:  return (Rectangle) { 96, 96 + offset, 48, 48 };	// Middle right
	case 6:  return (Rectangle) { 0, 96 + offset, 48, 48 };		// Lower left
	case 7:  return (Rectangle) { 48, 96 + offset, 48, 48 };	// Lower middle
	case 8:  return (Rectangle) { 96, 96 + offset, 48, 48 };	// Lower right

	case 9:  return (Rectangle) { 96, 0 + offset, 48, 48 };		// Round variant
	case 10: return (Rectangle) { 144, 0 + offset, 48, 48 };	// Corner 1 upper left
	case 11: return (Rectangle) { 192, 0 + offset, 48, 48 };	// Corner 1 upper right
	case 12: return (Rectangle) { 144, 48 + offset, 48, 48 };	// Corner 1 lower left
	case 13: return (Rectangle) { 192, 48 + offset, 48, 48 };	// Corner 1 lower right

	case 14: return (Rectangle) { 144, 96 + offset, 48, 48 };	// Corner 2 upper left
	case 15: return (Rectangle) { 192, 96 + offset, 48, 48 };	// Corner 2 upper right
	case 16: return (Rectangle) { 144, 144 + offset, 48, 48 };	// Corner 2 lower left
	case 17: return (Rectangle) { 192, 144 + offset, 48, 48 };	// Corner 2 lower right

	default:
		return (Rectangle) { 0, 0, 48, 48 };
	}
}

static void FieldTilesetInit() {
	Field2DTexture = LoadTexture("tilesets/field.png");

	Field.GrassVariant = FieldGrassVariants;
	Field.CleanGrassVariant = CleanGrassVariants;

	for (int i = 0; i < 18; i++) {
		// Grass
		FieldGrassVariants[i] = Drawable_Build(
			&Field2DTexture,
			GetFieldFloorVariantHelper(i, 0),	// Source
			(Vector2) { 0, 0 },			// Position
			(Vector2) {	1.0f, 1.0f },	// Scale
			(Vector2) {	0, 0 },			// Offset
			0.0f,						// Rotation
			WHITE						// Color
		);
		
		// Clean Grass
		CleanGrassVariants[i] = Drawable_Build(
			&Field2DTexture,
			GetFieldFloorVariantHelper(i, 3),	// Source
			(Vector2) {	0, 0 },			// Position
			(Vector2) {	1.0f, 1.0f },	// Scale
			(Vector2) {	0, 0 },			// Offset
			0.0f,						// Rotation
			WHITE						// Color
		);
	}

	Field.RockVariant = FieldRockVariants;

	for (int i = 0; i < 10; i++) {
		FieldRockVariants[i] = Drawable_Build(
			&Field2DTexture,	
			(Rectangle) { (float)(288 + 48 * i), 96, 48, 48	}, // Source
			(Vector2) { 0, 0 },			// Position
			(Vector2) {	1.0f, 1.0f },	// Scale
			(Vector2) {	0, 0 },			// Offset
			0.0f,						// Rotation
			WHITE						// Color
		);
	}
}

void TilesetTextures_Load(void) {
	FieldTilesetInit();
}

void TilesetTextures_Unload(void) {
	UnloadTexture(Field2DTexture);
}