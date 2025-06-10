#pragma once
#include "Drawable.h"
#include "List.h"

typedef struct Animation {
    int CurrentFrame;
    float ElapsedTime;
    float TimePerFrame;
    int StartingFrame;
    int EndingFrame;
    Drawable Drawable;
} Animation;

Animation Animation_Build(float time_per_frame, int starting_frame, int ending_frame, Drawable Drawable);

void Animation_Change(Animation* current_animation, Animation animation);
void Animation_Update(Animation* current_animation);
void Animation_Draw(Animation* current_animation);