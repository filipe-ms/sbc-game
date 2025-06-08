// MATH_UTILS_H

#pragma once

static inline int MathUtils_MinI(int a, int b) {
    return (a < b) ? a : b;
}

static inline int MathUtils_MaxI(int a, int b) {
    return (a > b) ? a : b;
}

static inline float MathUtils_ClampF(float value, float min, float max) {
    return value < min ? min : (value > max ? max : value);
}

float MathUtils_ClampFlagsF(float value, float min, float max, bool* hit_min, bool* hit_max) {
    if (hit_min) *hit_min = false;
    if (hit_max) *hit_max = false;

    if (value < min) {
        if (hit_min) *hit_min = true;
        return min;
    }
    if (value > max) {
        if (hit_max) *hit_max = true;
        return max;
    }
    return value;
}