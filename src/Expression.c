#include <Expression.h>
#include <AnimationMetadata.h>
#include <Animation.h>
#include <raymath.h>
#include "MathUtils.h"


void Expression_Init(Expression* expression, Expression_Type type) {
	expression->ElapsedTime = 0;
	expression->ElapsedTime = 0;
	expression->State = EXPRESSION_STATE_INACTIVE;
	expression->Position = &expression->Animation.Drawable.Position;
	expression->Animation.Drawable.Color = Fade(WHITE, 0);

	Expression_Change(expression, type);
}

void Expression_Update(Expression* expression)
{
	if (expression->State == EXPRESSION_STATE_INACTIVE) {
		return;
	}
	
	bool hasReachedMax = false;

	if (expression->State == EXPRESSION_STATE_SPAWNING) {
		expression->ElapsedTime = MathUtils_ClampFlagsF(expression->ElapsedTime + GetFrameTime(), 0, EXPRESSION_FADE_TIME, NULL, &hasReachedMax);
		float opacity = Normalize(expression->ElapsedTime, 0, EXPRESSION_FADE_TIME);
		expression->Animation.Drawable.Color = Fade(WHITE, opacity);

		if (hasReachedMax) {
			expression->ElapsedTime = 0;
			expression->State = EXPRESSION_STATE_ACTIVE;
		}
	}
	else if (expression->State == EXPRESSION_STATE_ACTIVE) {
		expression->ElapsedTime = MathUtils_ClampFlagsF(expression->ElapsedTime + GetFrameTime(), 0, EXPRESSION_ACTIVE_TIME, NULL, &hasReachedMax);

		if (hasReachedMax) {
			expression->ElapsedTime = EXPRESSION_FADE_TIME;
			expression->State = EXPRESSION_STATE_DESPAWNING;
		}
	}
	else if(expression->State == EXPRESSION_STATE_DESPAWNING) {
		expression->ElapsedTime = MathUtils_ClampFlagsF(expression->ElapsedTime - GetFrameTime(), 0, EXPRESSION_FADE_TIME, NULL, &hasReachedMax);
		float opacity = Normalize(expression->ElapsedTime, 0, EXPRESSION_FADE_TIME);
		expression->Animation.Drawable.Color = Fade(WHITE, opacity);

		if (hasReachedMax) {
			expression->ElapsedTime = 0;
			expression->State = EXPRESSION_STATE_INACTIVE;
		}
	}

	Animation_Update(&expression->Animation);
}

void Expression_Draw(Expression* expression)
{
	if (expression->State == EXPRESSION_STATE_INACTIVE)
		return;

	Animation_Draw(&expression->Animation);
}

void Expression_Change(Expression* expression, Expression_Type type) {
	expression->Type = type;

	if (expression->State == EXPRESSION_STATE_ACTIVE) {
		expression->ElapsedTime = 0;
		expression->State = EXPRESSION_STATE_ACTIVE;
	}
	else if (expression->State == EXPRESSION_STATE_DESPAWNING) {
		expression->State = EXPRESSION_STATE_SPAWNING;
	}
	else if (expression->State == EXPRESSION_STATE_INACTIVE) {
		expression->ElapsedTime = 0;
		expression->State = EXPRESSION_STATE_SPAWNING;
	}

	Animation_Change(&expression->Animation, *AnimationMetadata_GetMetadataByAnimatedExpressionType(type));

}