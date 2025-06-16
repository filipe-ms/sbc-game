#pragma once
#include <Building.h>

BuildingMetadata* BuildingMetadata_GetBuildingMetadataByType(Building_Type type);

void BuildingMetadata_Load(void);
void BuildingMetadata_Unload(void);