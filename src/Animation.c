#include "Animation.h"
//#include <SpecificLists.h>
#include "MathUtils.h"
#include "stdio.h"
#include "List.h"

LIST_IMPLEMENT(Animation)

static int GetNextFrame(Animation* animation);

// Public Methods
Animation Animation_Build(
    int current_frame, float elapsed_time, float time_per_frame,
    int starting_frame, int ending_frame, Drawable Drawable)
{
    Animation animation;
    animation.CurrentFrame = current_frame;
    animation.ElapsedTime = elapsed_time;
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
    int x = animation->Drawable.Texture->width / (int)animation->Drawable.Source.width;

    int column = (int)animation->CurrentFrame % x;
    int line = (int)animation->CurrentFrame / x; 

    int sourceWidth = animation->Drawable.Source.width;
    int sourceHeight = animation->Drawable.Source.height;

    animation->Drawable.Source = (Rectangle){
        column * sourceWidth,
        line* sourceHeight,
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

/*

AnimationInstance AnimationInstance_GetByIndex(List_AnimationInstance* list, int index) {
    return List_AnimationInstance_Find(list, IndexMatches);
}

int IndexMatches(AnimationInstance* instance, int* index) {
    return *index == instance->Index;
}*/

/*static Texture2D* GetBarbarianAction(Unit* unit) {
    switch (unit->state) {
    case MOVING: return &barbarian_walk;
    case ATTACKING: return &barbarian_attack;
    case IDLE: return &barbarian_idle;
    case PONDERING: return &barbarian_idle;
    default: return NULL;
    }
}*/


/*void DrawHero(Unit* unit) {
    if (!unit || unit->type != HERO || unit->stats.health.current <= 0) {
        return;
    }

    Texture2D* current_spritesheet = GetHeroAction(unit);

    if (current_spritesheet == NULL || current_spritesheet->id == 0) {
        TraceLog(LOG_WARNING, "DrawHero: No valid spritesheet for unit ID %d (Subtype: %d, State: %d).", unit->id, unit->subtype, unit->state);
        return;
    }

    float source_frame_width = 96.0f;
    float source_frame_height = 96.0f;
    int total_frames_in_animation = 4;
    float current_frame_duration = 0.20f;

    switch (unit->state) {
    case MOVING:
    case IDLE:
    case PONDERING:
        total_frames_in_animation = 4;
        current_frame_duration = 0.20f;
        break;
    case ATTACKING:
        total_frames_in_animation = 5;
        current_frame_duration = 0.15f;
        break;
    default:
        break;
    }

    float y_offset_on_spritesheet = source_frame_height * unit->animation.direction;

    if (unit->animation.current_texture_sheet != current_spritesheet) {
        unit->animation.current_texture_sheet = current_spritesheet;
        unit->animation.animation_time = 0.0f;
        unit->animation.current_frame = 0;
    }

    unit->animation.animation_time += GetFrameTime();
    if (unit->animation.animation_time >= current_frame_duration) {
        unit->animation.animation_time -= current_frame_duration;
        unit->animation.current_frame++;
        if (unit->subtype == SORCERER && unit->state == ATTACKING) {
            if (unit->animation.color.r == 102) {
                unit->animation.color = WHITE;
            }
            else unit->animation.color = SKYBLUE;
        }
        else {
            unit->animation.color = WHITE;
        }

        if (unit->animation.current_frame >= total_frames_in_animation) {
            if (unit->state == ATTACKING) {
                unit->animation.current_frame = 0;
                unit->stats.attack_ready = true;
            }
            else {
                unit->animation.current_frame = 0;
            }
        }

    }

    Rectangle source_rect = {
        source_frame_width * unit->animation.current_frame,
        y_offset_on_spritesheet,
        source_frame_width,
        source_frame_height
    };

    float target_visual_height_on_screen = TILE_SIZE * 1.5f;
    float aspect_ratio = source_frame_width / source_frame_height;
    if (source_frame_height == 0) aspect_ratio = 1.0f;
    float target_visual_width_on_screen = target_visual_height_on_screen * aspect_ratio;

    Rectangle hero_display_box = {
        unit->center.x - target_visual_width_on_screen / 2.0f,
        unit->center.y - target_visual_height_on_screen / 2.0f,
        target_visual_width_on_screen,
        target_visual_height_on_screen
    };

    DrawUnitSprite(
        unit->animation.current_texture_sheet,
        source_rect,
        hero_display_box,
        target_visual_height_on_screen,
        unit->animation.color
    );

    if (unit->is_selected) {
        DrawRectangleLinesEx(unit->box, 5.0f, RED);
    }
}*/
