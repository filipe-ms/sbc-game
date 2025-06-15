// File: Animation.c
#include "Animation.h"

#include "MathUtils.h"
#include "List.h"
#include "raymath.h"
#include <stdio.h>

static int GetNextFrame(Animation* animation);

// Public Methods
Animation Animation_Build(float time_per_frame, int starting_frame, int ending_frame, Drawable drawable)
{
    Animation animation;
    animation.CurrentFrame = starting_frame;
    animation.ElapsedTime = 0;
    animation.TimePerFrame = time_per_frame;
    animation.StartingFrame = starting_frame;
    animation.EndingFrame = ending_frame;
    animation.Drawable = drawable;
    animation.Order = ANIMATION_ORDER_FORWARD;
    animation.IsGoingForward = false;
    animation.OnAnimationStart = NULL;
    animation.OnAnimationEnd = NULL;
    animation.Owner = NULL;
    return animation;
}

Animation Animation_BuildWithOrder(float time_per_frame, int starting_frame, int ending_frame, Animation_Order order, Drawable drawable)
{
    Animation animation = Animation_Build(time_per_frame, starting_frame, ending_frame, drawable);
    animation.Order = order;
    return animation;
}

void Animation_AddTransitionEvents(Animation* animation, void* owner, Function_Arg1 onAnimationStart, Function_Arg1 onAnimationEnd)
{
    animation->Owner = owner;
    animation->OnAnimationStart = onAnimationStart;
    animation->OnAnimationEnd = onAnimationEnd;
}

void Animation_Change(Animation* current_animation, Animation animation) {
    
    /* AQUI NÃO MEXE NA DRAWABLE->POSITION DE PROPÓSITO */

    // Drawable
	current_animation->Drawable.Source = animation.Drawable.Source;
	current_animation->Drawable.Scale = animation.Drawable.Scale;
	current_animation->Drawable.Offset = animation.Drawable.Offset;
	current_animation->Drawable.Rotation = animation.Drawable.Rotation;
	current_animation->Drawable.Texture = animation.Drawable.Texture;
    
    // Animation
    current_animation->TimePerFrame = animation.TimePerFrame;
    current_animation->CurrentFrame = animation.StartingFrame;
    current_animation->StartingFrame = animation.StartingFrame;
    current_animation->EndingFrame = animation.EndingFrame;
    current_animation->ElapsedTime = 0.0f;
    current_animation->Order = animation.Order;
    current_animation->IsGoingForward = animation.IsGoingForward;
}

void Animation_Update(Animation* animation) {
    bool hasReachedMax;

    animation->ElapsedTime = MathUtils_ClampFlagsF(
        animation->ElapsedTime + GetFrameTime(),
        0, animation->TimePerFrame,
        NULL, &hasReachedMax);

    if (hasReachedMax) {
        animation->ElapsedTime = 0;
        animation->CurrentFrame = GetNextFrame(animation);
    }
}

void Animation_Draw(Animation* animation) {
    int framesPerRow = (int)animation->Drawable.Texture->width / (int)animation->Drawable.Source.width;

    int column = animation->CurrentFrame % framesPerRow;
    int line = animation->CurrentFrame / framesPerRow; 

    float sourceWidth = animation->Drawable.Source.width;
    float sourceHeight = animation->Drawable.Source.height;

    animation->Drawable.Source = (Rectangle){
        (float)column * sourceWidth,
        (float)line * sourceHeight,
        sourceWidth,
        sourceHeight
    };

	Drawable_Draw(&animation->Drawable);
}

// Private
static int GetNextFrame(Animation* animation) {
    if (animation->Order == ANIMATION_ORDER_FORWARD)
        return GetNextFrameFoward(animation);

    return GetNextFrameFowardAndBack(animation);
}

static int GetNextFrameFoward(Animation* animation) {
    int nextFrame = animation->CurrentFrame + 1;

    if (nextFrame == animation->EndingFrame) {
        Function_Invoke_Arg1(animation->OnAnimationEnd, animation->Owner);
    }

    if (nextFrame > animation->EndingFrame) {
        Function_Invoke_Arg1(animation->OnAnimationStart, animation->Owner);
        return animation->StartingFrame;
    }

    return nextFrame;
}

static int GetNextFrameFowardAndBack(Animation* animation) {
    if (animation->StartingFrame == animation->EndingFrame) {
        Function_Invoke_Arg1(animation->OnAnimationStart, animation->Owner);
        Function_Invoke_Arg1(animation->OnAnimationEnd, animation->Owner);
        return animation->StartingFrame;
    }

    if (animation->IsGoingForward) {
        int nextFrame = animation->CurrentFrame + 1;
        if (nextFrame > animation->EndingFrame) {
            animation->IsGoingForward = !animation->IsGoingForward;
            Function_Invoke_Arg1(animation->OnAnimationEnd, animation->Owner);
            return GetNextFrameFowardAndBack(animation);
        }

        return nextFrame;
    }

    int nextFrame = animation->CurrentFrame - 1;
    if (nextFrame < animation->StartingFrame) {
        animation->IsGoingForward = !animation->IsGoingForward;
        Function_Invoke_Arg1(animation->OnAnimationStart, animation->Owner);
        return GetNextFrameFowardAndBack(animation);
    }

    return nextFrame;
}