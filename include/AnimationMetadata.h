#pragma once
#include "Animation.h"
#include "raylib.h"
#include "List.h"

typedef struct AnimationMetadata {
    Texture2D Texture;
    List_Animation* AnimationInstanceList;
} AnimationMetadata;

LIST_DECLARE(AnimationMetadata)
LIST_DECLARE_FUNCTIONS(AnimationMetadata)
