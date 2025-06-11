#include "Animation.h"
#include <Constants.h>
#include "UnitMetadata.h"
#include <Unit.h>

// [ACTION][DIRECTION]
static Texture2D barbarian_idle_texture;
static Texture2D barbarian_walk_texture;
static Texture2D barbarian_attack_texture;
static Texture2D barbarian_faint_texture;

Animation* Barbarian = NULL;
UnitAnimationMetadata UnitAnimationmetadata[1];

UnitAnimationMetadata UnitMetadata_GetUnitAnimationMetadataByUnitType(Unit_Type type) {
    return UnitAnimationmetadata[type];
}

Animation* UnitMetadata_GetMetadataByUnitMetadataType(Unit_Type type)
{
    switch (type) {
    case BARBARIAN:
        return Barbarian;
    }

    return NULL;
}

static void BarbarianMetadataLoad(void) {
    UnitAnimationmetadata[BARBARIAN] = UnitAnimationMetadata_Build(4, 4);

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

    //          Malloc(sizeof(Animation) * action * directions)
    Barbarian = malloc(sizeof(Animation) * 4 * 4);

    if (!Barbarian) return;
    
    Barbarian[0] = Animation_Build(0.15f, 0, 3, barbIdleDrawable);   // Down
    Barbarian[1] = Animation_Build(0.15f, 4, 7, barbIdleDrawable);   // Left
    Barbarian[2] = Animation_Build(0.15f, 8, 11, barbIdleDrawable);  // Right
    Barbarian[3] = Animation_Build(0.15f, 12, 15, barbIdleDrawable); // Up

    Barbarian[4] = Animation_Build(0.15f, 0, 3, barbWalkDrawable);
    Barbarian[5] = Animation_Build(0.15f, 4, 7, barbWalkDrawable);
    Barbarian[6] = Animation_Build(0.15f, 8, 11, barbWalkDrawable);
    Barbarian[7] = Animation_Build(0.15f, 12, 15, barbWalkDrawable);

    Barbarian[8] = Animation_Build(0.15f, 0, 4, barbAttackDrawable);
    Barbarian[9] = Animation_Build(0.15f, 5, 9, barbAttackDrawable);
    Barbarian[10] = Animation_Build(0.15f, 10, 14, barbAttackDrawable);
    Barbarian[11] = Animation_Build(0.15f, 15, 19, barbAttackDrawable);

    Barbarian[12] = Animation_Build(0.15f, 0, 3, barbFaintDrawable);
    Barbarian[13] = Animation_Build(0.15f, 4, 7, barbFaintDrawable);
    Barbarian[14] = Animation_Build(0.15f, 8, 11, barbFaintDrawable);
    Barbarian[15] = Animation_Build(0.15f, 12, 15, barbFaintDrawable);
}

void UnitMetadata_Unload(void) {
	UnloadTexture(barbarian_idle_texture);
	UnloadTexture(barbarian_walk_texture);
	UnloadTexture(barbarian_attack_texture);
	UnloadTexture(barbarian_faint_texture);

    free(Barbarian);
}

void UnitMetadata_Load(void) {
	BarbarianMetadataLoad();
}