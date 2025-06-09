#include "Unit.h"
#include "Drawable.h"
#include "SpecificLists.h"

static void Barbarian_Load(void);
static void Barbarian_Unload(void);
static void Unit_ChangeDirection(Unit* unit, Unit_Direction direction);
static void Unit_ChangeAction(Unit* unit, Unit_Action action);

static int id = 0;

List_Unit_AnimationInstanceMetadata* G_BarbarianAnimationMetadataList;

const tile_size = 128;

static Drawable BuildDrawableMetadata(Texture2D* texture) {
    return (Drawable) {
        .Color = WHITE,
            .Offset = (Vector2){ 0 },
            .Destination = (Rectangle){ 0, 0, 128.0f, 128.0f },
            .Rotation = 0.0f,
            .Source = (Rectangle){ 0, 0, 96.0f, 96.0f },
            .Texture = texture,
    };
}

static Animation BuildAnimationState(Texture2D* texture, AnimationInstance instance) {
    return (Animation) {
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
    unit->Action = UNIT_ACTION_IDLE;
    unit->Direction = UNIT_DIRECTION_DOWN;
    
    Unit_AnimationInstanceMetadata* animationInstanceMetadata = List_Unit_AnimationInstanceMetadata_GetByIndex(G_BarbarianAnimationMetadataList, UNIT_ACTION_IDLE);
    AnimationInstance* animationInstance = List_AnimationInstance_GetByIndex(animationInstanceMetadata->AnimationInstanceList, UNIT_DIRECTION_DOWN);

    Animation_ChangeState(&unit->Animation, BuildAnimationState(&((*animationInstanceMetadata).Texture), *animationInstance));
}

void Unit_Load() {
    Barbarian_Load();
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
    Barbarian_Unload();
}

void Unit_Draw(Unit* unit) {
    Animation_Draw(&unit->Animation);
    DrawRectangleLinesEx(unit->Animation.Drawable.Destination, 5.0f, RED);
}

static void Unit_ChangeAction(Unit* unit, Unit_Action action) {
    unit->Action = action;

    Unit_AnimationInstanceMetadata* animationInstanceMetadata = List_Unit_AnimationInstanceMetadata_GetByIndex(G_BarbarianAnimationMetadataList, unit->Action);
    AnimationInstance* animationInstance = List_AnimationInstance_GetByIndex(animationInstanceMetadata->AnimationInstanceList, unit->Direction);

    Animation_ChangeAnimationInstance(&unit->Animation, *animationInstance);

    Animation_ChangeState(
        &unit->Animation,
        BuildAnimationState(
            &((*animationInstanceMetadata).Texture),
            *animationInstance
        )
    );
}

static void Unit_ChangeDirection(Unit* unit, Unit_Direction direction) {
    unit->Direction = direction;

    Unit_AnimationInstanceMetadata* animationInstanceMetadata = List_Unit_AnimationInstanceMetadata_GetByIndex(G_BarbarianAnimationMetadataList, unit->Action);
    AnimationInstance* animationInstance = List_AnimationInstance_GetByIndex(animationInstanceMetadata->AnimationInstanceList, unit->Direction);

    Animation_ChangeState(
        &unit->Animation,
        BuildAnimationState(
            unit->Animation.Drawable.Texture,
            *animationInstance
        )
    );
}

static AnimationInstance BuildAnimationInstance(int startingFrame, int endingFrame, int index) {
    AnimationInstance instance;
    instance.StartingFrame = startingFrame;
    instance.EndingFrame = endingFrame;
    instance.Index = index;
    return instance;
}

static void Barbarian_Load(void) {
    G_BarbarianAnimationMetadataList = List_Unit_AnimationInstanceMetadata_Create();

    // Idle
    Unit_AnimationInstanceMetadata barbarianIdle;
    barbarianIdle.Texture = LoadTexture("heroes/barbarian_idle.png");
    barbarianIdle.AnimationInstanceList = List_AnimationInstance_Create();

    List_AnimationInstance_AddToEnd(barbarianIdle.AnimationInstanceList, BuildAnimationInstance(0, 3, UNIT_DIRECTION_DOWN));
    List_AnimationInstance_AddToEnd(barbarianIdle.AnimationInstanceList, BuildAnimationInstance(4, 7, UNIT_DIRECTION_LEFT));
    List_AnimationInstance_AddToEnd(barbarianIdle.AnimationInstanceList, BuildAnimationInstance(8, 11, UNIT_DIRECTION_RIGHT));
    List_AnimationInstance_AddToEnd(barbarianIdle.AnimationInstanceList, BuildAnimationInstance(12, 15, UNIT_DIRECTION_UP));

    List_Unit_AnimationInstanceMetadata_AddToEnd(G_BarbarianAnimationMetadataList, barbarianIdle);


    // Walk
    Unit_AnimationInstanceMetadata barbarianWalk;
    barbarianWalk.Texture = LoadTexture("heroes/barbarian_walk.png");
    barbarianWalk.AnimationInstanceList = List_AnimationInstance_Create();

    List_AnimationInstance_AddToEnd(barbarianWalk.AnimationInstanceList, BuildAnimationInstance(0, 3, UNIT_DIRECTION_DOWN));
    List_AnimationInstance_AddToEnd(barbarianWalk.AnimationInstanceList, BuildAnimationInstance(4, 7, UNIT_DIRECTION_LEFT));
    List_AnimationInstance_AddToEnd(barbarianWalk.AnimationInstanceList, BuildAnimationInstance(8, 11, UNIT_DIRECTION_RIGHT));
    List_AnimationInstance_AddToEnd(barbarianWalk.AnimationInstanceList, BuildAnimationInstance(12, 15, UNIT_DIRECTION_UP));

    List_Unit_AnimationInstanceMetadata_AddToEnd(G_BarbarianAnimationMetadataList, barbarianWalk);

    // Attack 
    Unit_AnimationInstanceMetadata barbarianAttack;
    barbarianAttack.Texture = LoadTexture("heroes/barbarian_attack.png");
    barbarianAttack.AnimationInstanceList = List_AnimationInstance_Create();

    List_AnimationInstance_AddToEnd(barbarianAttack.AnimationInstanceList, BuildAnimationInstance(0, 4, UNIT_DIRECTION_DOWN));
    List_AnimationInstance_AddToEnd(barbarianAttack.AnimationInstanceList, BuildAnimationInstance(5, 9, UNIT_DIRECTION_LEFT));
    List_AnimationInstance_AddToEnd(barbarianAttack.AnimationInstanceList, BuildAnimationInstance(10, 14, UNIT_DIRECTION_RIGHT));
    List_AnimationInstance_AddToEnd(barbarianAttack.AnimationInstanceList, BuildAnimationInstance(15, 19, UNIT_DIRECTION_UP));

    List_Unit_AnimationInstanceMetadata_AddToEnd(G_BarbarianAnimationMetadataList, barbarianAttack);
}

static void Barbarian_Unload(void) {
    List_Node_Unit_AnimationInstanceMetadata* node = G_BarbarianAnimationMetadataList->head;

    for (; node != NULL; node = node->next) {
        UnloadTexture(node->data.Texture);
        List_AnimationInstance_Free(node->data.AnimationInstanceList);
    }

    List_Unit_AnimationInstanceMetadata_Free(G_BarbarianAnimationMetadataList);
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

