#include <math.h>

#include "player.h"


player_input get_player_input(void) {
    player_input input = {0};
    if (IsKeyDown(KEY_LEFT)) input.rotation -= 1.0f;
    if (IsKeyDown(KEY_RIGHT)) input.rotation += 1.0f;
    if (IsKeyDown(KEY_UP)) input.thrust += 1.0f;
    if (IsKeyDown(KEY_DOWN)) input.thrust -= 1.0f;
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
}

void wrap_player_on_screen(entity *player, int screen_width, int screen_height) {
    if (player->x < 0) player->x = (float)screen_width;
    if (player->x > (float)screen_width) player->x = 0;
    if (player->y < 0) player->y = (float)screen_height;
    if (player->y > (float)screen_height) player->y = 0;
}