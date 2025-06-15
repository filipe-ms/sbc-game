// File: UnitAnimationMetadata.c
#include "UnitAnimationMetadata.h"

UnitAnimationMetadata UnitAnimationMetadata_Build(int actions, int directions) {
    UnitAnimationMetadata unitAnimationMetadata;
    unitAnimationMetadata.Actions = actions;
    unitAnimationMetadata.Directions = directions;
    return unitAnimationMetadata;
}