// File: AnimationMetadata.h
#pragma once

#include "Unit.h"
#include "Button.h"

UnitAnimationMetadata AnimationMetadata_GetUnitAnimationMetadataByUnitType(Unit_Type type);
Animation* AnimationMetadata_GetMetadataByAnimationMetadataType(Unit_Type type);
void AnimationMetadata_Load(void);
void AnimationMetadata_Unload(void);

Animation* AnimationMetadata_GetMetadataByAnimatedButtonType(AnimatedButton_Type type);
