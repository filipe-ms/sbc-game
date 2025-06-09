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

LIST_DECLARE(Animation)
LIST_DECLARE_FUNCTIONS(Animation)

Animation Animation_Build(
    int current_rame, float elapsed_time, float time_per_frame,
    int starting_frame, int ending_frame, Drawable Drawable);

Animation Animation_BuildAnimation(
    Texture2D* texture, Animation* animation);

Animation Animation_BuildWithReference(
    Texture2D* texture, int starting_frame, int ending_frame);


void Animation_Change(Animation* current_animation, Animation animation);
void Animation_Update(Animation* current_animation);
void Animation_Draw(Animation* current_animation);