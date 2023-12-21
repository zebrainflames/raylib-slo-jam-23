#pragma once

#include "raylib.h" // <-- For Texture2D -- TODO: replace with renderer.h or something

typedef struct entity_s {
    float x, y, vx, vy;
    float rotation;
    float health;
    float scale;
} entity;

entity create_entity(float x, float y);

void update_entity(entity *e, float dt);

void draw_entity(entity *e, Texture2D tex);
