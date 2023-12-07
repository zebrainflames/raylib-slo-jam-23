#pragma once

#include "raylib.h"

#include "textures/textures.h"

typedef struct game {
    int should_quit;
    int scene; // placeholder
    // assets
    texture_manager *tm;
    
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