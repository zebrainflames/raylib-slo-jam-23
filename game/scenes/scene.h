#pragma once

#include <stdlib.h>

///#include "../game.h"
#include "../entities/entity.h"

typedef struct scene_s {
    entity* asteroids;
    entity* projectiles;
    entity* player;
    entity* enemies;

    // function pointers to track scene enter, exit, update and render capabilities
    void (*enter)(void);
    void (*exit)(void);
    void (*update)(struct scene_s* s);
    void (*render)(struct scene_s* s, void* g);
    // Optional functions to track scene changes -- can be NULL for some scenes
    struct scene_s* previous;
    struct scene_s* next;
} scene;


scene* scene_base_new(void);

void scene_render(scene* s, void* g);

void scene_update(scene* s);

void scene_enter(scene* s);

void scene_exit(scene* s);


/// <summary>
/// Test scene implementation, can be used as an eample for other scenes
/// </summary>
typedef struct scene_testing {
    scene* base;
} scene_testing;

void scene_update_testing(scene *s);

void scene_render_testing(scene *s, void* g);

void scene_init_testing(scene_testing *s);

void scene_free_testing(scene_testing *s);

