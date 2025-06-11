#pragma once
#include <UnitAnimationMetadata.h>
#include <Unit.h>

UnitAnimationMetadata UnitMetadata_GetUnitAnimationMetadataByUnitType(Unit_Type type);
Animation* UnitMetadata_GetMetadataByUnitMetadataType(Unit_Type type);
void UnitMetadata_Load(void);
void UnitMetadata_Unload(void);
