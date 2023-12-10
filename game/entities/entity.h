#pragma once

typedef struct entity_s {
    float x, y, vx, vy;
} entity;

entity create_entity(float x, float y);

void update_entity(entity *e, float dt);

void draw_entity(entity *e);
