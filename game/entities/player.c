#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "player.h"

#define PLAYER_COLOR CLITERAL(Color){ 220, 246, 200, 255 }

bool player_shoot_primary = false;
//static bool player_shoot_seconday = false;

static inline bool left_pressed(void) {
    return IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A);
}

static inline bool right_pressed(void) {
    return IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D);
}

static inline bool up_pressed(void) {
    return IsKeyDown(KEY_UP) || IsKeyDown(KEY_W);
}

static inline bool down_pressed(void) {
    return IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S);
}

static float time_since_primary = 0.0f;

player_input get_player_input(void) {
    player_input input = {0};
    if (left_pressed()) input.rotation -= 1.0f;
    if (right_pressed()) input.rotation += 1.0f;
    if (up_pressed()) input.thrust -= 1.0f;
    if (down_pressed()) input.thrust += 1.0f;
    if (IsKeyDown(KEY_SPACE)) input.shoot_primary = true;
    return input;

}

void update_player(entity *player, player_input input, float dt) {
    player->rotation += input.rotation * PLAYER_ROTATION_SPEED * dt;
    player->vx *= PLAYER_DRAG_FACTOR;
    player->vy *= PLAYER_DRAG_FACTOR;
    float dvx = cosf(player->rotation * DEG2RAD + PI/2.0f) * PLAYER_ACCELERATION * dt;
    float dvy = sinf(player->rotation * DEG2RAD + PI/2.0f) * PLAYER_ACCELERATION * dt;
    player->vy += dvy * input.thrust;
    player->vx += dvx * input.thrust;
    update_entity(player, dt);

    if (time_since_primary >= PLAYER_PRIMARY_COOLDOWN && input.shoot_primary) {
        time_since_primary = 0.0f;
        player_shoot_primary = true;
    } else {
        player_shoot_primary = false;
    }
    time_since_primary += dt;
}

void wrap_player_on_screen(entity *player, int screen_width, int screen_height) {
    if (player->x < 0) player->x = (float)screen_width;
    if (player->x > (float)screen_width) player->x = 0;
    if (player->y < 0) player->y = (float)screen_height;
    if (player->y > (float)screen_height) player->y = 0;
}


void draw_player(entity *player, Texture2D tex) {
    Vector2 origin = {tex.width/2 * player->scale, tex.height/2 * player->scale};
    DrawTexturePro(
        tex, 
        (Rectangle){0, 0, (float)tex.width, (float)tex.height}, 
        (Rectangle){player->x, player->y, tex.width*player->scale, tex.height*player->scale}, 
        origin, 
        player->rotation, 
        PLAYER_COLOR
    );
}

entity* create_player(float x, float y) {
    entity* player = calloc(1, sizeof(entity));
    if (player == NULL)
    {
        fprintf(stderr, "FAILED TO ALLOCATE MEMORY FOR PLAYER!\n");
        exit(EXIT_FAILURE);
    }
    player->scale = 0.125f; // TODO: update art and set scale to 1.0f
    player->x = x;
    player->y = y;
    player->health = 100.0f;
    return player;
}