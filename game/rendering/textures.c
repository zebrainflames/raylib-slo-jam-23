#include <stdlib.h>

#include "textures.h"

static texture_manager* tm = NULL;

#define PLAYER_SHIP_TEX "assets/selected/ship_G.png"
#define METEOR_TEX "assets/selected/meteor_squareDetailedLarge.png"
#define BULLET_TEX "assets/selected/bullet_basic.png"


void tm_load_textures(texture_manager *tex) {
    tex->player_tex = LoadTexture(PLAYER_SHIP_TEX);
    tex->meteor_tex = LoadTexture(METEOR_TEX);   
    tex->bullet_tex = LoadTexture(BULLET_TEX);
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
    UnloadTexture(tex->meteor_tex);
    UnloadTexture(tex->bullet_tex);
    free(tex);
}