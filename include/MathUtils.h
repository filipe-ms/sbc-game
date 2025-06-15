// File: MathUtils.h
#pragma once

#include "stdbool.h"

inline int MathUtils_MinI(int a, int b);
inline int MathUtils_MaxI(int a, int b);
float MathUtils_ClampF(float value, float min, float max);
float MathUtils_ClampFlagsF(float value, float min, float max, bool* hit_min, bool* hit_max);