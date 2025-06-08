#include "Unit.h"
#include "Drawable.h"
//#include "SpecificLists.h"

static void Barbarian_Load(void);
static void Barbarian_Unload(void);
static void Unit_ChangeDirection(Unit* unit, Direction direction);

static int id = 0;

Texture2D barbarian_walk;
Texture2D barbarian_attack;
Texture2D barbarian_faint;
Texture2D barbarian_idle;

//typedef struct Unit_Metadata {
    //List_Texture2D Textures;
    //List_AnimationInstance AnimationInstance[4];
//} Unit_Metadata;

//Unit_Metadata metadata;

const AnimationInstance BarbarianAnimationInstance_Idle[4] = {
    {
        .StartingFrame = 0,
        .EndingFrame = 3,
        .Index = DIRECTION_DOWN,
    }, {
        .StartingFrame = 4,
        .EndingFrame = 7,
        .Index = DIRECTION_LEFT,
    }, {
        .StartingFrame = 8,
        .EndingFrame = 11,
        .Index = DIRECTION_RIGHT,
    }, {
        .StartingFrame = 12,
        .EndingFrame = 15,
        .Index = DIRECTION_UP,
    }
};

const AnimationInstance BarbarianAnimationInstance_Walk[4] = {
    {
        .StartingFrame = 0,
        .EndingFrame = 3,
        .Index = DIRECTION_DOWN,
    }, {
        .StartingFrame = 4,
        .EndingFrame = 7,
        .Index = DIRECTION_LEFT,
    }, {
        .StartingFrame = 8,
        .EndingFrame = 11,
        .Index = DIRECTION_RIGHT,
    }, {
        .StartingFrame = 12,
        .EndingFrame = 15,
        .Index = DIRECTION_UP,
    }
};

const AnimationInstance BarbarianAnimationInstance_Attacking[4] = {
    {
        .StartingFrame = 0,
        .EndingFrame = 3,
        .Index = DIRECTION_DOWN,
    }, {
        .StartingFrame = 4,
        .EndingFrame = 7,
        .Index = DIRECTION_LEFT,
    }, {
        .StartingFrame = 8,
        .EndingFrame = 11,
        .Index = DIRECTION_RIGHT,
    }, {
        .StartingFrame = 12,
        .EndingFrame = 15,
        .Index = DIRECTION_UP,
    }
};

const tile_size = 128;

static Drawable_Metadata BuildDrawableMetadata(Texture2D* texture) {
    return (Drawable_Metadata) {
        .Color = WHITE,
            .Offset = (Vector2){ 0 },
            .Destination = (Rectangle){ 0, 0, 128.0f, 128.0f },
            .Rotation = 0.0f,
            .Source = (Rectangle){ 0, 0, 96.0f, 96.0f },
            .Texture = texture,
    };
}

static AnimationState BuildAnimationState(Texture2D* texture, AnimationInstance instance) {
    return (AnimationState) {
        .AnimationInstance = instance,
            .CurrentFrame = instance.StartingFrame,
            .ElapsedTime = 0.0f,
            .TimePerFrame = 0.25f,
            .Drawable = BuildDrawableMetadata(texture)
    };
}

// Barbarian
void Unit_Init(Unit* unit) {
    unit->Id = id++;    
    AnimationState_ChangeState(&unit->Animation, BuildAnimationState(&barbarian_idle, BarbarianAnimationInstance_Idle[0]));
}

void Unit_Load() {
    Barbarian_Load();
}

void Unit_Update(Unit* unit) {
    AnimationState_Update(&unit->Animation);

    if (IsKeyPressed(KEY_W)) {
        Unit_ChangeDirection(unit, DIRECTION_UP);
    }
    else if (IsKeyPressed(KEY_A)) {
        Unit_ChangeDirection(unit, DIRECTION_LEFT);
    }
    else if (IsKeyPressed(KEY_S)) {
        Unit_ChangeDirection(unit, DIRECTION_DOWN);
    }
    else if (IsKeyPressed(KEY_D)) {
        Unit_ChangeDirection(unit, DIRECTION_RIGHT);
    }
    else if (IsKeyPressed(KEY_F1)) {

    }
    else if (IsKeyPressed(KEY_F2)) {

    }
}

void Unit_Unload() {
    Barbarian_Unload();
}

void Unit_Draw(Unit* unit) {
    AnimationState_Draw(&unit->Animation);
    DrawRectangleLinesEx(unit->Animation.Drawable.Destination, 5.0f, RED);
}

static void Unit_ChangeDirection(Unit* unit, Direction direction) {
    unit->Direction = direction;

    AnimationState_ChangeState(
        &unit->Animation,
        BuildAnimationState(
            unit->Animation.Drawable.Texture, BarbarianAnimationInstance_Walk[direction]
        )
    );
}

static void Unit_ChangeAnimation(Unit* unit, AnimationState animation) {
    AnimationState_ChangeState(
        &unit->Animation,
        BuildAnimationState(
            &barbarian_idle,
            BarbarianAnimationInstance_Idle[DIRECTION_DOWN]
        )
    );
}

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

