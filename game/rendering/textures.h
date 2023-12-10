#pragma once

#include "raylib.h"

typedef struct texture_manager {
    Texture2D player_tex;

} texture_manager;


texture_manager* texture_manager_init();

void texture_manager_free(texture_manager *tm);