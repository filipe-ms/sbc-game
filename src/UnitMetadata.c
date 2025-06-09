#include "Animation.h"
#include "AnimationMetadata.h"

List_AnimationMetadata* G_BarbarianAnimationMetadataList;

static void BarbarianMetadataLoad(void);
static void BarbarianMetadataUnload(void);

void UnitMetadata_Load() {
    BarbarianMetadataLoad();
}

void UnitMetadata_Unload() {
    BarbarianMetadataUnload();
}

static void BarbarianMetadataLoad(void) {
    G_BarbarianAnimationMetadataList = List_AnimationMetadata_Create();

    // Idle
    AnimationMetadata barbarianIdle;
    barbarianIdle.Texture = LoadTexture("heroes/barbarian_idle.png");
    barbarianIdle.AnimationInstanceList = List_Animation_Create();

    List_Animation_AddToEnd(barbarianIdle.AnimationInstanceList, Animation_BuildWithReference(&barbarianIdle.Texture, 0, 3)); // Up
    List_Animation_AddToEnd(barbarianIdle.AnimationInstanceList, Animation_BuildWithReference(&barbarianIdle.Texture, 4, 7)); // Left
    List_Animation_AddToEnd(barbarianIdle.AnimationInstanceList, Animation_BuildWithReference(&barbarianIdle.Texture, 8, 11)); // Right
    List_Animation_AddToEnd(barbarianIdle.AnimationInstanceList, Animation_BuildWithReference(&barbarianIdle.Texture, 12, 15)); // Down

    List_AnimationMetadata_AddToEnd(G_BarbarianAnimationMetadataList, barbarianIdle);

    // Walk
    AnimationMetadata barbarianWalk;
    barbarianWalk.Texture = LoadTexture("heroes/barbarian_walk.png");
    barbarianWalk.AnimationInstanceList = List_Animation_Create();

    List_Animation_AddToEnd(barbarianWalk.AnimationInstanceList, Animation_BuildWithReference(&barbarianWalk.Texture, 0, 3));
    List_Animation_AddToEnd(barbarianWalk.AnimationInstanceList, Animation_BuildWithReference(&barbarianWalk.Texture, 4, 7));
    List_Animation_AddToEnd(barbarianWalk.AnimationInstanceList, Animation_BuildWithReference(&barbarianWalk.Texture, 8, 11));
    List_Animation_AddToEnd(barbarianWalk.AnimationInstanceList, Animation_BuildWithReference(&barbarianWalk.Texture, 12, 15));

    List_AnimationMetadata_AddToEnd(G_BarbarianAnimationMetadataList, barbarianWalk);

    // Attack 
    AnimationMetadata barbarianAttack;
    barbarianAttack.Texture = LoadTexture("heroes/barbarian_attack.png");
    barbarianAttack.AnimationInstanceList = List_Animation_Create();

    List_Animation_AddToEnd(barbarianAttack.AnimationInstanceList, Animation_BuildWithReference(&barbarianAttack.Texture, 0, 4));
    List_Animation_AddToEnd(barbarianAttack.AnimationInstanceList, Animation_BuildWithReference(&barbarianAttack.Texture, 5, 9));
    List_Animation_AddToEnd(barbarianAttack.AnimationInstanceList, Animation_BuildWithReference(&barbarianAttack.Texture, 10, 14));
    List_Animation_AddToEnd(barbarianAttack.AnimationInstanceList, Animation_BuildWithReference(&barbarianAttack.Texture, 15, 19));

    List_AnimationMetadata_AddToEnd(G_BarbarianAnimationMetadataList, barbarianAttack);
}
static void BarbarianMetadataUnload(void) {
    List_Node_AnimationMetadata* node = G_BarbarianAnimationMetadataList->head;

    for (; node != NULL; node = node->next) {
        UnloadTexture(node->data.Texture);
        List_Animation_Free(node->data.AnimationInstanceList);
    }

    List_AnimationMetadata_Free(G_BarbarianAnimationMetadataList);
}