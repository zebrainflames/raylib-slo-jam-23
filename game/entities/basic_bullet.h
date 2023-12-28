#pragma once

#include "entity.h"

entity create_basic_bullet(float x, float y, float vx, float vy, float rotation) {
    entity e = create_entity(x, y);
    e.rotation = rotation;
    e.vx = vx;
    e.vy = vy;
    return e;
}