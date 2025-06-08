#pragma once

#include "Unit.h"
#include "Drawable.h"

Texture2D barbarian_walk;
Texture2D barbarian_attack;
Texture2D barbarian_faint;
Texture2D barbarian_idle;

static int id = 0;

static void Barbarian_Load(void) {
    barbarian_walk = LoadTexture("heroes/barbarian_walk.png");
    barbarian_attack = LoadTexture("heroes/barbarian_attack.png");
    barbarian_faint = LoadTexture("heroes/barbarian_faint.png");
    barbarian_idle = LoadTexture("heroes/barbarian_idle.png");
}

static void Barbarian_Unload(void) {
    UnloadTexture(barbarian_walk);
    UnloadTexture(barbarian_attack);
    UnloadTexture(barbarian_faint);
    UnloadTexture(barbarian_idle);
}

const tile_size = 128;

static void Drawable_Metadata_Init(Drawable_Metadata* drawable) {
    drawable->Color = WHITE;
    drawable->Offset = (Vector2){ 0 };
    drawable->Destination = (Rectangle){ 0, 0, 128.0f, 128.0f };
    drawable->Rotation = 0.0f;
    drawable->Source = (Rectangle){ 0, 0, 96.0f, 96.0f };
    drawable->Texture = &barbarian_walk;
}

static void Animation_Init(AnimationState* animationState) {
    animationState->CurrentFrame = 0;
    animationState->ElapsedTime = 0;
    Drawable_Metadata_Init(&animationState->Drawable);
}

// Barbarian
void Unit_Init(Unit* unit) {
    unit->id = id++;
    Animation_Init(&unit->Animation);

    return unit;
}

void Unit_Load() {
    Barbarian_Load();
}

void Unit_Update(Unit* unit) {
    AnimationState_Update(&unit->Animation);
}

void Unit_Unload() {
    Barbarian_Unload();
}

void Unit_Draw(Unit* unit) {
    AnimationState_Draw(&unit->Animation);
    DrawRectangleLinesEx(unit->Animation.Drawable.Destination, 5.0f, RED);
}

static void DrawUnitSprite(Texture2D* texture, Rectangle source_rect, Rectangle display_box, float target_visual_height, Color tint) {
    if (texture == NULL || texture->id == 0 || source_rect.width <= 0 || source_rect.height <= 0) {
        TraceLog(LOG_WARNING, "DrawUnitSprite: Invalid texture or zero-size source_rect.");
        return;
    }
    if (target_visual_height <= 0) {
        TraceLog(LOG_WARNING, "Invalid height.");
        return;
    }
    Rectangle exact_dest_rect = display_box;
    DrawTexturePro(*texture, source_rect, exact_dest_rect, (Vector2) { 0, 0 }, 0.0f, tint);
}

/*
void DrawHero(Unit* unit) {

    Texture2D* current_spritesheet = &barbarian_idle;

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
}
*/

