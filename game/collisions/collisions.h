#pragma once

#include <raylib.h>

typedef struct {
    float depth;
    float nx, ny;
} collision_result;

collision_result resolveRects(Rectangle* a, Rectangle* b);
