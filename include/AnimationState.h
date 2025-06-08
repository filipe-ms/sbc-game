#pragma once
#include <Drawable.h>

typedef enum Direction {
    DIRECTION_NONE = -1,
    DIRECTION_DOWN = 0,
    DIRECTION_LEFT = 1,
    DIRECTION_RIGHT = 2,
    DIRECTION_UP = 3
} Direction;

typedef struct AnimationState {
    int CurrentFrame;
    float ElapsedTime;
    float TimePerFrame;
    Drawable_Metadata Drawable;
} AnimationState;

void AnimationState_GetNextFrame(AnimationState* animation);
void AnimationState_Update(AnimationState* animation);
void AnimationState_Draw(AnimationState* animation);