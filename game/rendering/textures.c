#include <stdlib.h>

#include "textures.h"

static texture_manager* tm = NULL;

#define PLAYER_SHIP_TEX "assets/vector/scout.png"

void tm_load_textures(texture_manager *tex) {
    tex->player_tex = LoadTexture(PLAYER_SHIP_TEX);    
}

texture_manager* texture_manager_init() {
    if (tm == NULL) {
        tm = malloc(sizeof(texture_manager));
    }
    tm_load_textures(tm);
    return tm;
}

// free textures and texture manager
void texture_manager_free(texture_manager *tex) {
    UnloadTexture(tex->player_tex);
    free(tex);
}