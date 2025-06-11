#pragma once
typedef struct UnitAnimationMetadata {
    int Actions;
    int Directions;
} UnitAnimationMetadata;

UnitAnimationMetadata UnitAnimationMetadata_Build(int actions, int directions);