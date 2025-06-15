// File: Animation.h
#pragma once

#include "Drawable.h"
#include "Function.h"

typedef enum Animation_Order {
    ANIMATION_ORDER_FORWARD,
    ANIMATION_ORDER_FORWARD_AND_BACK,
} Animation_Order;

typedef struct Animation {
    int CurrentFrame;
    float ElapsedTime;
    float TimePerFrame;
    int StartingFrame;
    int EndingFrame;
    Drawable Drawable;

    Animation_Order Order;
    bool IsGoingForward;


    void* Owner;
    Function_Arg1 OnAnimationStart;
    Function_Arg1 OnAnimationEnd;
} Animation;

Animation Animation_Build(float time_per_frame, int starting_frame, int ending_frame, Drawable Drawable);
Animation Animation_BuildWithOrder(float time_per_frame, int starting_frame, int ending_frame, Animation_Order order, Drawable drawable);

void Animation_AddTransitionEvents(Animation* animation, void* owner, Function_Arg1 onAnimationStart, Function_Arg1 onAnimationFinish);

void Animation_Change(Animation* current_animation, Animation animation);
void Animation_Update(Animation* current_animation);
void Animation_Draw(Animation* current_animation);