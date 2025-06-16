#include <BuildingHologram.h>
#include <Building.h>
#include <GameInputManager.h>
#include <raylib.h>
#include <raymath.h>

static const Color HOLOGRAM_GREEN = {
	.r = 125,
	.g = 200,
	.b = 125,
	.a = 150,
};

static const Color HOLOGRAM_INTENSITY_RANGE = {
	.r = 20,
	.g = 40,
	.b = 10,
	.a = 25,
};

static void UpdatePosition(BuildingHologram* buildingHologram) {
	Vector2 mousepos = GameInputManager_GetMouseToWorld2D();
	Vector2 gridpos = GameInputManager_ConvertToGridSnapInputCoordinate(mousepos);

	*buildingHologram->Position = gridpos;
}

static void UpdateBuildCommands() {

}

static void UpdateTransparencyEffect(BuildingHologram* buildingHologram) {
	buildingHologram->ElapsedTime = fmod(buildingHologram->ElapsedTime + GetFrameTime() * PI, 2.0f * PI);
	buildingHologram->Color->r = HOLOGRAM_GREEN.r + HOLOGRAM_INTENSITY_RANGE.r * cosf(buildingHologram->ElapsedTime);
	buildingHologram->Color->g = HOLOGRAM_GREEN.g + HOLOGRAM_INTENSITY_RANGE.g * cosf(buildingHologram->ElapsedTime);
	buildingHologram->Color->b = HOLOGRAM_GREEN.b + HOLOGRAM_INTENSITY_RANGE.b * cosf(buildingHologram->ElapsedTime);
	buildingHologram->Color->a = HOLOGRAM_GREEN.a + HOLOGRAM_INTENSITY_RANGE.a * cosf(buildingHologram->ElapsedTime);
}

void BuildingHologram_Init(BuildingHologram* buildingHologram, Building_Type type) {
	buildingHologram->Color = &buildingHologram->Building.Drawable.Color;
	buildingHologram->Position = &buildingHologram->Building.Drawable.Position;

	Building_Init(&buildingHologram->Building, type);
}

void BuildingHologram_Update(BuildingHologram* buildingHologram) {
	if (!buildingHologram->IsActive) return;

	UpdatePosition(buildingHologram);
	UpdateTransparencyEffect(buildingHologram);
	
	UpdateBuildCommands(buildingHologram);

	Building_Update(&buildingHologram->Building);
}


void BuildingHologram_Draw(BuildingHologram* buildingHologram) {
	if (!buildingHologram->IsActive) return;

	Building_Draw(&buildingHologram->Building);

	Rectangle destination = Drawable_CalculateDestination(&buildingHologram->Building.Drawable);
	destination.x = buildingHologram->Building.Position->x - buildingHologram->Building.Drawable.Offset.x;
	destination.y = buildingHologram->Building.Position->y - buildingHologram->Building.Drawable.Offset.y;
	DrawRectangleLinesEx(destination, 5, RED);
}