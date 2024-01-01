#pragma once

#include <math.h>

#include "raylib.h"

#include "entity.h"

#define BASIC_BULLET_SPEED 350.0f
#define BASIC_BULLET_SIZE 10.0f
#define BASIC_BULLET_DAMAGE 10.0f
#define BASIC_BULLET_KNOCKBACK 5.0f
 
entity create_basic_bullet(float x, float y, float vx, float vy, float rotation) {
    entity e = create_entity(x, y);
    e.rotation = rotation;
    e.vx = cosf(rotation*DEG2RAD - PI/2.0f) * BASIC_BULLET_SPEED;
    e.vy = sinf(rotation*DEG2RAD - PI/2.0f) * BASIC_BULLET_SPEED;
    return e;
}