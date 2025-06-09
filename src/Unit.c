#include "Unit.h"
#include "Drawable.h"
#include "SpecificLists.h"
#include "AnimationMetadata.h"
#include "UnitMetadata.h"

// Public
void Unit_Init(Unit* unit) {
    unit->Action = UNIT_ACTION_IDLE;
    unit->Direction = UNIT_DIRECTION_DOWN;
    
    AnimationMetadata* animationInstanceMetadata = List_AnimationMetadata_GetByIndex(G_BarbarianAnimationMetadataList, UNIT_ACTION_IDLE);
    Animation* animationInstance = List_Animation_GetByIndex(animationInstanceMetadata->AnimationInstanceList, UNIT_DIRECTION_DOWN);

    Animation newAnimation = Animation_BuildAnimation(&((*animationInstanceMetadata).Texture), animationInstance);
    Animation_Change(&unit->Animation, newAnimation);
}

void Unit_Load() {

}

void Unit_Update(Unit* unit) {
    Animation_Update(&unit->Animation);

    if (IsKeyPressed(KEY_W)) {
        Unit_ChangeDirection(unit, UNIT_DIRECTION_UP);
    }
    else if (IsKeyPressed(KEY_A)) {
        Unit_ChangeDirection(unit, UNIT_DIRECTION_LEFT);
    }
    else if (IsKeyPressed(KEY_S)) {
        Unit_ChangeDirection(unit, UNIT_DIRECTION_DOWN);
    }
    else if (IsKeyPressed(KEY_D)) {
        Unit_ChangeDirection(unit, UNIT_DIRECTION_RIGHT);
    }
    else if (IsKeyPressed(KEY_F1)) {
        Unit_ChangeAction(unit, UNIT_ACTION_ATTACK);
    }
    else if (IsKeyPressed(KEY_F2)) {
        Unit_ChangeAction(unit, UNIT_ACTION_IDLE);
    }
}

void Unit_Unload() {

}

void Unit_Draw(Unit* unit) {
    Animation_Draw(&unit->Animation);
    DrawRectangleLinesEx(unit->Animation.Drawable.Destination, 5.0f, RED);
}

void Unit_ChangeDirection(Unit* unit, Unit_Direction direction) {
    unit->Direction = direction;

    AnimationMetadata* animationInstanceMetadata = List_AnimationMetadata_GetByIndex(G_BarbarianAnimationMetadataList, unit->Action);
    Animation* animationInstance = List_Animation_GetByIndex(animationInstanceMetadata->AnimationInstanceList, unit->Direction);

    Animation newAnimation = Animation_BuildAnimation(&((*animationInstanceMetadata).Texture), animationInstance);

    Animation_Change(&unit->Animation, newAnimation);
}

void Unit_ChangeAction(Unit* unit, Unit_Action action) {
    unit->Action = action;

    AnimationMetadata* animationInstanceMetadata = List_AnimationMetadata_GetByIndex(G_BarbarianAnimationMetadataList, unit->Action);
    Animation* animationInstance = List_Animation_GetByIndex(animationInstanceMetadata->AnimationInstanceList, unit->Direction);
    
    Animation newAnimation = Animation_BuildAnimation(&((*animationInstanceMetadata).Texture), animationInstance);

    Animation_Change(&unit->Animation, newAnimation);
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

