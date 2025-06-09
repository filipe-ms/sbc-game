#pragma once
#include <Drawable.h>

typedef struct AnimationInstance {
    int StartingFrame;
    int EndingFrame;
    int Index;
} AnimationInstance;

typedef struct Animation {
    int CurrentFrame;
    float ElapsedTime;
    float TimePerFrame;
    Drawable Drawable;
    AnimationInstance AnimationInstance;
} Animation;

void Animation_ChangeAnimationInstance(Animation* animation, AnimationInstance instance);
void Animation_ChangeState(Animation* animation, Animation state);
void Animation_Update(Animation* animation);
void Animation_Draw(Animation* animation);