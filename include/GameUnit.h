#pragma once

#include "stdbool.h"

#include "Unit.h"

typedef enum UnitAnimationMetadata_Direction {
    GAMEUNIT_DIRECTION_NONE = -1,
    GAMEUNIT_DIRECTION_DOWN = 0,
    GAMEUNIT_DIRECTION_LEFT = 1,
    GAMEUNIT_DIRECTION_RIGHT = 2,
    GAMEUNIT_DIRECTION_UP = 3
} Unit_Direction;

typedef enum UnitAnimationMetadata_Action {
    GAMEUNIT_ACTION_NONE = -1,
    GAMEUNIT_ACTION_IDLE = 0,
    GAMEUNIT_ACTION_WALK = 1,
    GAMEUNIT_ACTION_ATTACK = 2,
    GAMEUNIT_ACTION_FAINT = 3,
} GameUnit_Action;

typedef enum GameUnit_Type {
    GAMEUNIT_TYPE_NONE = -1,
} GameUnit_Type;

typedef enum GameUnit_SubType {
    GAMEUNIT_SUBTYPE_NONE = -1,
}GameUnit_SubType;

typedef struct GameUnit {
	GameUnit_Type Type;
	GameUnit_SubType SubType;

	GameUnit_Action Action;

	bool IsClickable;

	Unit Unit;

} GameUnit;

void GameUnit_Init(GameUnit* game_unit);
void GameUnit_Load(GameUnit* game_unit);
void GameUnit_Update(GameUnit* game_unit);
void GameUnit_Draw(GameUnit* game_unit);
