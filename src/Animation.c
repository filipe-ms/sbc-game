#include "Animation.h"
//#include <SpecificLists.h>
#include "MathUtils.h"
#include "stdio.h"
#include "List.h"

static int GetNextFrame(Animation* animation);

// Public Methods
Animation Animation_Build(float time_per_frame, int starting_frame, int ending_frame, Drawable Drawable)
{
    Animation animation;
    animation.CurrentFrame = starting_frame;
    animation.ElapsedTime = 0;
    animation.TimePerFrame = time_per_frame;
    animation.StartingFrame = starting_frame;
    animation.EndingFrame = ending_frame;
    animation.Drawable = Drawable;

    return animation;
}

void Animation_Change(Animation* current_animation, Animation animation) {
    current_animation->Drawable = animation.Drawable;
    current_animation->TimePerFrame = animation.TimePerFrame;
    current_animation->CurrentFrame = animation.StartingFrame;
    current_animation->StartingFrame = animation.StartingFrame;
    current_animation->EndingFrame = animation.EndingFrame;
    current_animation->ElapsedTime = 0.0f;
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
    int nextFrame = animation->CurrentFrame + 1;
    if (nextFrame > animation->EndingFrame) {
        return animation->StartingFrame;
    }

    return nextFrame;
}