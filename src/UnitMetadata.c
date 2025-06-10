#include "Animation.h"
#include "AnimationMetadata.h"
#include <Constants.h>

// [ACTION][DIRECTION]
static Texture2D barbarian_idle_texture;
static Texture2D barbarian_walk_texture;
static Texture2D barbarian_attack_texture;
static Texture2D barbarian_faint_texture;
Animation Barbarian[4][4];

Animation UnitMetadata_GetMetadataIndex(int action, int direction) {
	return Barbarian[action][direction];
}

static void BarbarianMetadataLoad(void) {

    barbarian_idle_texture = LoadTexture("heroes/barbarian_idle.png");
    barbarian_walk_texture = LoadTexture("heroes/barbarian_walk.png");
    barbarian_attack_texture = LoadTexture("heroes/barbarian_attack.png");
    barbarian_faint_texture = LoadTexture("heroes/barbarian_faint.png");

    Rectangle sourceRect = { 0, 0, 96, 96 };
    Vector2 scale = { CONSTANTS_TILE_SIZE_F /96, CONSTANTS_TILE_SIZE_F  / 96 };
    
    Drawable barbIdleDrawable = Drawable_Build(&barbarian_idle_texture, sourceRect, (Vector2) { 0, 0 }, scale, (Vector2) { 0, 0 }, 0.0f, WHITE);
    Drawable barbWalkDrawable = Drawable_Build(&barbarian_walk_texture, sourceRect, (Vector2) { 0, 0 }, scale, (Vector2) { 0, 0 }, 0.0f, WHITE);
    Drawable barbAttackDrawable = Drawable_Build(&barbarian_attack_texture, sourceRect, (Vector2) { 0, 0 }, scale, (Vector2) { 0, 0 }, 0.0f, WHITE);
    Drawable barbFaintDrawable = Drawable_Build(&barbarian_faint_texture, sourceRect, (Vector2) { 0, 0 }, scale, (Vector2) { 0, 0 }, 0.0f, WHITE);

    Barbarian[0][0] = Animation_Build(0.15f, 0, 3, barbIdleDrawable);   // Down
    Barbarian[0][1] = Animation_Build(0.15f, 4, 7, barbIdleDrawable);   // Left
    Barbarian[0][2] = Animation_Build(0.15f, 8, 11, barbIdleDrawable);  // Right
    Barbarian[0][3] = Animation_Build(0.15f, 12, 15, barbIdleDrawable); // Up

    Barbarian[1][0] = Animation_Build(0.15f, 0, 3, barbWalkDrawable);
    Barbarian[1][1] = Animation_Build(0.15f, 4, 7, barbWalkDrawable);
    Barbarian[1][2] = Animation_Build(0.15f, 8, 11, barbWalkDrawable);
    Barbarian[1][3] = Animation_Build(0.15f, 12, 15, barbWalkDrawable);

    Barbarian[2][0] = Animation_Build(0.15f, 0, 4, barbAttackDrawable);
    Barbarian[2][1] = Animation_Build(0.15f, 5, 9, barbAttackDrawable);
    Barbarian[2][2] = Animation_Build(0.15f, 10, 14, barbAttackDrawable);
    Barbarian[2][3] = Animation_Build(0.15f, 15, 19, barbAttackDrawable);

    Barbarian[3][0] = Animation_Build(0.15f, 0, 3, barbFaintDrawable);
    Barbarian[3][1] = Animation_Build(0.15f, 4, 7, barbFaintDrawable);
    Barbarian[3][2] = Animation_Build(0.15f, 8, 11, barbFaintDrawable);
    Barbarian[3][3] = Animation_Build(0.15f, 12, 15, barbFaintDrawable);
}

void UnitMetadata_Unload(void) {
	UnloadTexture(barbarian_idle_texture);
	UnloadTexture(barbarian_walk_texture);
	UnloadTexture(barbarian_attack_texture);
	UnloadTexture(barbarian_faint_texture);
}

void UnitMetadata_Load(void) {
	BarbarianMetadataLoad();
}