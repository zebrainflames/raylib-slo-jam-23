#pragma once

#include "raylib.h" // <-- For Texture2D -- TODO: replace with renderer.h or something

#define ASTEROID_COLLISION_DAMAGE 55.0f

// Colors
#define ASTEROID_COLOR  CLITERAL(Color){ 255, 137, 51, 255 }
#define BULLET_COLOR    CLITERAL(Color){ 255, 255, 255, 255 }
#define ENEMY_COLOR     CLITERAL(Color){ 204, 47, 123, 255 }

typedef struct entity_s {
    float x, y, vx, vy;
    float rotation;
    float health;
    float scale;
} entity;

entity create_entity(float x, float y);

void update_entity(entity *e, float dt);

void draw_entity(entity *e, Texture2D tex);

void draw_entity_color(entity *e, Texture2D tex, Color color);