#include "entity.h"

entity create_entity(float x, float y) {
    entity e;
    e.x = x;
    e.y = y;
    e.vx = 0;
    e.vy = 0;
    return e;
}

void update_entity(entity *e, float dt) {
    e->x += e->vx * dt;
    e->y += e->vy * dt;
}

void draw_entity(entity *e) {
    
}