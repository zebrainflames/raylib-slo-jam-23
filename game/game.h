#pragma once

#include "raylib.h"

#include "game/scenes/scene.h"
#include "rendering/textures.h"

#define UPDATE_FPS 60
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define UPDATE_FPS 60


typedef struct game {
    int should_quit;
    // assets
    texture_manager *tm;
    
    // scene setup
    scene *current_scene;
    scene **scenes;
    int scene_amount;

    // testing...    
    int tx, ty; // testing variables
    int ix, iy; // game input tests..

} game;


int game_window_should_close(game *g);

void game_init(game *g);

void game_get_input(game *g);

void game_update(game *g);

void game_draw(game *g);

void game_quit(game *g);