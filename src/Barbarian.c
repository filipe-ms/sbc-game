// DRAW.C
// Barbarian

/*
Texture2D barbarian_walk;
Texture2D barbarian_attack;
Texture2D barbarian_faint;
Texture2D barbarian_idle;

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

static Texture2D* GetBarbarianAction(Unit* unit) {
    switch (unit->state) {
    case MOVING: return &barbarian_walk;
    case ATTACKING: return &barbarian_attack;
    case IDLE: return &barbarian_idle;
    case PONDERING: return &barbarian_idle;
    default: return NULL;
    }
}

static Texture2D* GetHeroAction(Unit* unit) {
    switch (unit->subtype) {
    case BARBARIAN: return GetBarbarianAction(unit);
    case SORCERER: return GetSorcererAction(unit);
    default: return NULL;
    }
}

void DrawHero(Unit* unit) {
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
}

    // Barbarian
    barbarian_walk = LoadTexture("heroes/barbarian_walk.png");
    barbarian_attack = LoadTexture("heroes/barbarian_attack.png");
    barbarian_faint = LoadTexture("heroes/barbarian_faint.png");
    barbarian_idle = LoadTexture("heroes/barbarian_idle.png");

    // Barbarian
    UnloadTexture(barbarian_walk);
    UnloadTexture(barbarian_attack);
    UnloadTexture(barbarian_faint);
    UnloadTexture(barbarian_idle);

// UNIT.C AI EMBAIXO


static void InitUnitAnimationState(AnimationState* animation) {
    if (!animation) return;
    animation->current_texture_sheet = NULL;
    animation->animation_time = 0.0f;
    animation->current_frame = 0;
    animation->color = WHITE;
    animation->direction = DOWN;

    animation->current_expression_texture = NULL;
    animation->expression_time = 0.0f;
    animation->current_expression_frame = 0;
    animation->loop_direction = 1;
}

static void InitUnitStats(CombatStats* stats, SubType subtype) {
    if (!stats) return;
    stats->level = 1;
    stats->health.current = 100; stats->health.max = 100;
    stats->mana.current = 50; stats->mana.max = 50;
    stats->experience.current = 0; stats->experience.max = 20;
    stats->attack = 10;
    stats->defense = 5;
    stats->attack_range = 1;
    stats->sight_range = 5;
    stats->attack_range = false;
    stats->attack_ready = false;
    stats->regen_rate = 0.0f;
    stats->resistance = 0.0f; // Resistência inicial é 0.0f
    

    switch (subtype) {
    case BARBARIAN:
        stats->health.current = 150; stats->health.max = 150;
        stats->attack = 15;
        stats->sight_range = 6;

        break;
    case SORCERER:
        stats->health.current = 80; stats->health.max = 80;
        stats->mana.current = 100; stats->mana.max = 100;
        stats->attack = 23;
        stats->attack_range = 3;
        stats->sight_range = 8;
        break;
    case SATYR:
        stats->health.current = 70; stats->health.max = 70;
        stats->attack = 12;
        stats->sight_range = 4;
        break;
    case SKELETON:
        stats->health.current = 90; stats->health.max = 90;
        stats->attack = 12;
        stats->sight_range = 5;
        break;
    case BEAST:
        stats->health.current = 120; stats->health.max = 120;
        stats->attack = 14;
        stats->sight_range = 3;
        break;
    case LICH:
        stats->health.current = 500; stats->health.max = 500;
        stats->mana.current = 200; stats->mana.max = 200;
        stats->attack = 25;
        stats->defense = 1;
        stats->attack_range = 4;
        stats->sight_range = 7;
        break;
    case TOWN_HALL:
        stats->health.current = 500; stats->health.max = 500;
        stats->mana.current = 0; stats->mana.max = 0;
        stats->attack = 0;
        stats->defense = 2;
        stats->attack_range = 0;
        stats->sight_range = 0;
        break;
    case TENT:
        stats->health.current = 200; stats->health.max = 200;
        stats->mana.current = 0; stats->mana.max = 0;
        stats->attack = 0;
        stats->defense = 1;
        stats->attack_range = 0;
        stats->sight_range = 0;
        break;
    case HOUSE:
        stats->health.current = 150; stats->health.max = 150;
        stats->mana.current = 0; stats->mana.max = 0;
        stats->attack = 0;
        stats->defense = 1;
        stats->attack_range = 0;
        stats->sight_range = 0;
        break;
    default:
        break;
    }
    stats->healthptr = &stats->health;
}

int GetBuildingGoldCost(SubType building_type) {
    switch (building_type) {
    case TENT:
        return 150;
    case BARBARIAN:
        return 50;
    case HOUSE:
        return 100;
    case SORCERER:
        return 55;
    default:
        return 99999;
    }
}

static void InitUnitBuildStats(BuildStats* build_stats, SubType subtype) {
    if (!build_stats) return;
    build_stats->cost = GetBuildingGoldCost(subtype);
    build_stats->progress.current = 0;
    build_stats->progress.max = 100;
}

static void InitUnitMovement(Movement* movement, Type type, SubType subtype) {
    if (!movement) return;

    movement->path = NULL;
    movement->path_node_index = NONE;

    if (type == HERO) {
        if (subtype == BARBARIAN) movement->speed = 250.0f;
        else if (subtype == SORCERER) movement->speed = 200.0f;
    } else if (type == MONSTER){
        if (subtype == SATYR) movement->speed = 150.0f;
        else if (subtype == SKELETON) movement->speed = 150.0f;
        else if (subtype == BEAST) movement->speed = 200.0f;
        else if (subtype == LICH) movement->speed = 50.0f;
    }
}

static void InitUnitAiState(AiState* ai) {
    if (!ai) return;
    ai->personality = GetRandomValue(0, 1) * ALL;
    ai->request_cooldown = 0.0f;
    ai->is_awaiting_response = false;
    ai->previous_decisions = malloc(1 * sizeof(char));
    if (ai->previous_decisions) {
        ai->previous_decisions[0] = '\0';
    }
    else {
        TraceLog(LOG_ERROR, "Falha ao alocar previous_decisions para IA da unidade.");
    }
}

static void InitUnit(Unit* unit, Type type, SubType subtype, Vector2 initial_center_pos, int id) {
    if (!unit) return;

    InitUnitAnimationState(&unit->animation);
    InitUnitStats(&unit->stats, subtype);
    InitUnitMovement(&unit->movement, type, subtype);
    InitUnitAiState(&unit->ai);
    InitUnitBuildStats(&unit->build, subtype);

    unit->id = id;
    unit->type = type;
    unit->subtype = subtype;
    unit->is_selected = false;

    if (type == HERO) {
        unit->mood = HAPPY;
        unit->state = IDLE;
    } else if (type == MONSTER) {
        unit->mood = NONE;
        unit->state = IDLE;
    }
    else {
        unit->mood = NONE;
        unit->state = NONE;
    }

    unit->position.x = -1;
    unit->position.y = -1;
    unit->position.isValid = false;
    unit->position.tile = TILE_INVALID;

    unit->box.width = TILE_SIZE;
    unit->box.height = TILE_SIZE;
    unit->center = initial_center_pos;
    unit->box.x = unit->center.x - unit->box.width / 2.0f;
    unit->box.y = unit->center.y - unit->box.height / 2.0f;

    unit->target_unit = NULL;
    unit->to_remove = false;

    unit->reserved_destination_tile.isValid = false;
    unit->reserved_destination_tile.x = -1;
    unit->reserved_destination_tile.y = -1;
    unit->reserved_destination_tile.tile = TILE_INVALID;

    UpdateUnitGridPosition(unit);
}
*/