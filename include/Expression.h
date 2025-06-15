#pragma once
#include "Animation.h"

#define EXPRESSION_FADE_TIME 0.5f
#define EXPRESSION_ACTIVE_TIME 3.0f

typedef enum Expression_State {
	EXPRESSION_STATE_INACTIVE,
	EXPRESSION_STATE_SPAWNING,
	EXPRESSION_STATE_ACTIVE,
	EXPRESSION_STATE_DESPAWNING
} Expression_State;

typedef enum Expression_Type {
	EXPRESSION_ANGRY = 0,
	EXPRESSION_CURIOUS,
	EXPRESSION_YES,
	EXPRESSION_HAPPY,
	EXPRESSION_NERVOUS,
	EXPRESSION_SAD,
	EXPRESSION_SURPRISED,
	EXPRESSION_THINKING,
} Expression_Type;

typedef struct Expression {
	Vector2* Position;

	float ElapsedTime;

	Expression_State State;
	Expression_Type Type;
	Animation Animation;
} Expression;

void Expression_Init(Expression* expression, Expression_Type type);
void Expression_Update(Expression* expression);
void Expression_Draw(Expression* expression);

void Expression_Change(Expression* expression, Expression_Type type);