// UNITMETADATA_C

#include "AnimationMetadata.h"

#include "Animation.h"
#include "Constants.h"
#include "Unit.h"

#include <stdlib.h>
#include <Button.h>
#include <Expression.h>

static void AnimatedButton_BloodMetadataLoad(void);
static void GameUnit_BarbarianMetadataLoad(void);
static void Expressions_MetadataLoad(void);

static Texture2D barbarian_idle_texture;
static Texture2D barbarian_walk_texture;
static Texture2D barbarian_attack_texture;
static Texture2D barbarian_faint_texture;

Animation* Barbarian = NULL;
UnitAnimationMetadata UnitAnimationmetadata[1];

static Texture2D AnimatedButton_Blood_Texture;

// Public
Animation* AnimationMetadata_GetMetadataByAnimationMetadataType(Unit_Type type)
{
    switch (type) {
    case BARBARIAN:
        return Barbarian;
    }

    return NULL;
}

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

void AnimationMetadata_Load(void) {
    GameUnit_BarbarianMetadataLoad();
    AnimatedButton_BloodMetadataLoad();
    Expressions_MetadataLoad();
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

static Texture2D expression_angry_texture;
static Texture2D expression_curious_texture;
static Texture2D expression_yes_texture;
static Texture2D expression_happy_texutre;
static Texture2D expression_nervous_texture;
static Texture2D expression_sad_texture;
static Texture2D expression_surprised_texture;
static Texture2D expression_thinking_texture;

Animation AnimationMetadata_ExpressionMetadata[8] = { 0 };

Animation* AnimationMetadata_GetMetadataByAnimatedExpressionType(Expression_Type type) {
    return &AnimationMetadata_ExpressionMetadata[type];
}

// Private
static void Expressions_MetadataLoad(void) {
    expression_angry_texture = LoadTexture("expressions/angry.png");
    expression_curious_texture = LoadTexture("expressions/curious.png");
    expression_yes_texture = LoadTexture("expressions/yes.png");
    expression_happy_texutre = LoadTexture("expressions/happy.png");
    expression_nervous_texture = LoadTexture("expressions/nervous.png");
    expression_sad_texture = LoadTexture("expressions/sad.png");
    expression_surprised_texture = LoadTexture("expressions/surprised.png");
    expression_thinking_texture = LoadTexture("expressions/thinking.png");

    Rectangle source = (Rectangle){ 0, 0, 32, 27 };
    Vector2 scale = (Vector2){ 1, 1 };

    Drawable drawable_angry = Drawable_Build(&expression_angry_texture, source, (Vector2) { 0, 0 }, scale, (Vector2) { 0, 0 }, 0.0f, WHITE);
    Drawable drawable_curious = Drawable_Build(&expression_curious_texture, source, (Vector2) { 0, 0 }, scale, (Vector2) { 0, 0 }, 0.0f, WHITE);
    Drawable drawable_yes = Drawable_Build(&expression_yes_texture, source, (Vector2) { 0, 0 }, scale, (Vector2) { 0, 0 }, 0.0f, WHITE);
    Drawable drawable_happy = Drawable_Build(&expression_happy_texutre, source, (Vector2) { 0, 0 }, scale, (Vector2) { 0, 0 }, 0.0f, WHITE);
    Drawable drawable_nervous = Drawable_Build(&expression_nervous_texture, source, (Vector2) { 0, 0 }, scale, (Vector2) { 0, 0 }, 0.0f, WHITE);
    Drawable drawable_sad = Drawable_Build(&expression_sad_texture, source, (Vector2) { 0, 0 }, scale, (Vector2) { 0, 0 }, 0.0f, WHITE);
    Drawable drawable_surprised = Drawable_Build(&expression_surprised_texture, source, (Vector2) { 0, 0 }, scale, (Vector2) { 0, 0 }, 0.0f, WHITE);
    Drawable drawable_thinking = Drawable_Build(&expression_thinking_texture, source, (Vector2) { 0, 0 }, scale, (Vector2) { 0, 0 }, 0.0f, WHITE);

    float speed = 0.3f;

    AnimationMetadata_ExpressionMetadata[EXPRESSION_ANGRY] = Animation_BuildWithOrder(speed, 0, 3, ANIMATION_ORDER_FORWARD_AND_BACK, drawable_angry);
    AnimationMetadata_ExpressionMetadata[EXPRESSION_CURIOUS] = Animation_BuildWithOrder(speed, 0, 4, ANIMATION_ORDER_FORWARD_AND_BACK, drawable_curious);
    AnimationMetadata_ExpressionMetadata[EXPRESSION_HAPPY] = Animation_BuildWithOrder(speed, 0, 3, ANIMATION_ORDER_FORWARD_AND_BACK, drawable_happy);
    AnimationMetadata_ExpressionMetadata[EXPRESSION_NERVOUS] = Animation_BuildWithOrder(speed, 0, 3, ANIMATION_ORDER_FORWARD_AND_BACK, drawable_nervous);
    AnimationMetadata_ExpressionMetadata[EXPRESSION_SAD] = Animation_BuildWithOrder(speed, 0, 3, ANIMATION_ORDER_FORWARD_AND_BACK, drawable_sad);
    AnimationMetadata_ExpressionMetadata[EXPRESSION_SURPRISED] = Animation_BuildWithOrder(speed, 0, 4, ANIMATION_ORDER_FORWARD_AND_BACK, drawable_surprised);
    AnimationMetadata_ExpressionMetadata[EXPRESSION_THINKING] = Animation_BuildWithOrder(speed, 0, 4, ANIMATION_ORDER_FORWARD_AND_BACK, drawable_thinking);
    AnimationMetadata_ExpressionMetadata[EXPRESSION_YES] = Animation_BuildWithOrder(speed, 0, 3, ANIMATION_ORDER_FORWARD_AND_BACK, drawable_yes);
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

static void GameUnit_BarbarianMetadataLoad(void) {
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

