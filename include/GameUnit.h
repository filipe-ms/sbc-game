// File: GameUnit.h
#pragma once

#include "stdbool.h"
#include "Button.h"
#include "Unit.h"
#include "Drawable.h"
#include "Unit.h"
#include "GenList.h"

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

typedef struct GameUnit_PositionalData {
    Vector2* Position;          // Ponteiro para a posição real da unidade (ligado ao Drawable).
    Vector2 FinalDestination;   // O destino final no grid, definido pelo jogador.
    Vector2 NextWaypoint;       // O próximo ponto imediato no *mundo* para onde a unidade deve se mover.
    List* Path;                 // A lista de pontos (no grid) que formam o caminho até o FinalDestination.
} PositionalData;

typedef struct GameUnit {
	bool IsClickable;
    bool IsBeingHovered;
	Unit Unit;

	Vector2* Position;
    Vector2 Destination;
    TransparentButton TransparentButton;

	PositionalData PositionalData;
} GameUnit;


void GameUnit_Init(GameUnit* unit, Unit_Type type);
void GameUnit_Update(GameUnit* unit);
void GameUnit_Draw(GameUnit* unit);

Rectangle GameUnit_CalculateCollisionBounds(GameUnit* unit);
