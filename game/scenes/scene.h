#pragma once

#include <stdlib.h>

#include "../entities/entity.h"

typedef struct scene_s {
    entity* asteroids;
    entity* projectiles;
    entity* player;
    entity* enemies;

    // function pointers to track scene enter, exit, update and render capabilities
    void (*enter)(void);
    void (*exit)(void);
    void (*update)(void);
    void (*render)(void);
    // Optional functions to track scene changes -- can be NULL for some scenes
    struct scene_s* (*next_scene)(void);
    struct scene_s* (*previous_scene)(void);
} scene;

typedef struct scene_testing {
    scene* base;
    // testing variables
    int tx, ty; // testing variables
    int ix, iy; // game input tests..
} scene_testing;

scene* scene_base_new(void);

void scene_update_testing(void);

void scene_render_testing(void);

void scene_init_testing(scene_testing *s);

void scene_free_testing(scene_testing *s);

