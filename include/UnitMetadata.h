// UNITMETADATA_H

#pragma once

#include "Unit.h"
#include "Button.h"

UnitAnimationMetadata UnitMetadata_GetUnitAnimationMetadataByUnitType(Unit_Type type);
Animation* UnitMetadata_GetMetadataByUnitMetadataType(Unit_Type type);
void UnitMetadata_Load(void);
void UnitMetadata_Unload(void);

Animation* UnitMetadata_GetMetadataByAnimatedButtonType(AnimatedButton_Type type);
