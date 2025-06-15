// UNITMETADATA_H

#pragma once

#include "Unit.h"
#include "Button.h"
#include "Expression.h"

extern Animation AnimationMetadata_ExpressionMetadata[8];

UnitAnimationMetadata AnimationMetadata_GetUnitAnimationMetadataByUnitType(Unit_Type type);
Animation* AnimationMetadata_GetMetadataByAnimatedButtonType(AnimatedButton_Type type);
Animation* AnimationMetadata_GetMetadataByAnimationMetadataType(Unit_Type type);
Animation* AnimationMetadata_GetMetadataByAnimatedExpressionType(Expression_Type type);

void AnimationMetadata_Load(void);
void AnimationMetadata_Unload(void);

