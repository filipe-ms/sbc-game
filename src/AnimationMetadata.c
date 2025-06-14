// File: AnimationMetadata.c
#include "AnimationMetadata.h"

#include "Animation.h"
#include "Button.h"
#include "Constants.h"
#include "Unit.h"

#include <stdlib.h>



static Texture2D barbarian_idle_texture;
static Texture2D barbarian_walk_texture;
static Texture2D barbarian_attack_texture;
static Texture2D barbarian_faint_texture;

Animation* Barbarian = NULL;
UnitAnimationMetadata UnitAnimationmetadata[1];

Animation* AnimationMetadata_GetMetadataByAnimationMetadataType(Unit_Type type)
{
    switch (type) {
    case BARBARIAN:
        return Barbarian;
    }

    return NULL;
}

// Button Animations
static Texture2D AnimatedButton_Blood_Texture;
Animation* Blood = NULL;

Animation* AnimationMetadata_GetMetadataByAnimatedButtonType(AnimatedButton_Type type) {
    switch (type) {
    case ANIMATEDBUTTON_TYPE_BLOOD:
        return Blood;
    }

    return NULL;
}

UnitAnimationMetadata AnimationMetadata_GetUnitAnimationMetadataByUnitType(Unit_Type type) {
    return UnitAnimationmetadata[type];
}

static void AnimatedButton_BloodMetadataLoad(void) {
    Blood = malloc(sizeof(Animation) * 4);

    if (!Blood) return;

    AnimatedButton_Blood_Texture = LoadTexture("ui/blood.png");

    Rectangle source = (Rectangle){ 0, 0, 37, 36 };
    Vector2 scale = (Vector2){ 1, 1 };

    Drawable blood_normal = Drawable_Build(&AnimatedButton_Blood_Texture, source, (Vector2) { 0, 0 }, scale, (Vector2) { 0, 0 }, 0.0f, WHITE);
    Drawable blood_hovered = Drawable_Build(&AnimatedButton_Blood_Texture, source, (Vector2) { 0, 0 }, scale, (Vector2) { 0, 0 }, 0.0f, WHITE);
    Drawable blood_clicked = Drawable_Build(&AnimatedButton_Blood_Texture, source, (Vector2) { 0, 0 }, scale, (Vector2) { 0, 0 }, 0.0f, WHITE);
    Drawable blood_active = Drawable_Build(&AnimatedButton_Blood_Texture, source, (Vector2) { 0, 0 }, scale, (Vector2) { 0, 0 }, 0.0f, WHITE);

    Blood[0] = Animation_Build(0.0f, 0, 0, blood_normal);
    Blood[1] = Animation_Build(0.0f, 1, 1, blood_hovered);
    Blood[2] = Animation_Build(0.0f, 2, 2, blood_clicked);
    Blood[3] = Animation_Build(0.0f, 3, 3, blood_active);
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

void AnimationMetadata_Unload(void) {
	UnloadTexture(barbarian_idle_texture);
	UnloadTexture(barbarian_walk_texture);
	UnloadTexture(barbarian_attack_texture);
	UnloadTexture(barbarian_faint_texture);

    free(Barbarian);

    // Buttons
    UnloadTexture(AnimatedButton_Blood_Texture);
    free(Blood);
}

void AnimationMetadata_Load(void) {
	BarbarianMetadataLoad();
    AnimatedButton_BloodMetadataLoad();
}