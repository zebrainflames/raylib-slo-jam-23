#pragma once

#include <stdlib.h>

///#include "../game.h"
#include "../entities/entity.h"
#include "game_state.h"

typedef struct scene_s {
    entity* asteroids;
    entity* projectiles;
    entity* player;
    entity* enemies;

    // 
    game_state current_state;

    // function pointers to track scene enter, exit, update and render capabilities
    void (*enter)(void);
    void (*exit)(void);
    void (*update)(struct scene_s* s);
    void (*render)(struct scene_s* s, void* g);
    void (*free_scene)(struct scene_s* s); // free all scene resources, also from the associated parent/scene implementation struct
    // Optional functions to track scene changes -- can be NULL for some scenes
    struct scene_s* previous;
    struct scene_s* next;
    // parent pointer, currently only used in freeing all memory associated with a scene
    void* parent;
} scene;


scene* scene_base_new(void);

void scene_render(scene* s, void* g);

void scene_update(scene* s);

void scene_enter(scene* s);

void scene_exit(scene* s);

void scene_free(scene* s);


/// <summary>
/// Test scene implementation, can be used as an eample for other scenes
/// </summary>
typedef struct scene_testing {
    scene* base;
} scene_testing;

void scene_reset_testing(scene *s);

void scene_update_testing(scene *s);

void scene_render_testing(scene *s, void* g);

scene* scene_init_testing(void);

void scene_free_testing(scene *s);

