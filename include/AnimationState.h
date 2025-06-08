#pragma once
#include <Drawable.h>
//#include <SpecificLists.h>

typedef struct AnimationInstance {
    int StartingFrame;
    int EndingFrame;
    int Index;
} AnimationInstance;

typedef struct AnimationState {
    int CurrentFrame;
    float ElapsedTime;
    float TimePerFrame;
    Drawable_Metadata Drawable;
    AnimationInstance AnimationInstance;
} AnimationState;

void AnimationState_ChangeAnimationInstance(AnimationState* animation, AnimationInstance instance);
void AnimationState_ChangeState(AnimationState* animation, AnimationState state);
void AnimationState_Update(AnimationState* animation);
void AnimationState_Draw(AnimationState* animation);


//AnimationInstance AnimationInstance_GetByIndex(List_AnimationInstance* list, int index);