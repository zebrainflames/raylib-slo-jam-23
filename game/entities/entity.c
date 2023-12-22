#include "raylib.h"

#include "entity.h"

entity create_entity(float x, float y) {
    entity e = {
        .x = x,
        .y = y,
        .vx = 0,
        .vy = 0,
        .rotation = 0,
        .health = 100,
        .scale = 1.0f
    };
    return e;
}

void update_entity(entity *e, float dt) {
    e->x += e->vx * dt;
    e->y += e->vy * dt;
}

void draw_entity(entity *e, Texture2D tex) {
    // scale needs to be taken into account in setting up the origin for correct rotations
    Vector2 origin = {tex.width/2 * e->scale, tex.height/2 * e->scale};
    DrawTexturePro(tex, (Rectangle){0, 0, (float)tex.width, (float)tex.height}, (Rectangle){e->x, e->y, tex.width*e->scale, tex.height*e->scale}, origin, e->rotation, WHITE);
}