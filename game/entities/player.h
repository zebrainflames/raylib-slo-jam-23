#pragma once

#include <stdbool.h>

#include "entity.h"

#define PLAYER_MAX_SPEED 100.0f
#define PLAYER_ACCELERATION 100.0f
#define PLAYER_ROTATION_SPEED 180.0f
#define PLAYER_DRAG_FACTOR 0.994f
#define PLAYER_COLLIDER_SIZE 20.0f

// TODO: replace these with weapon definitions
#define PLAYER_PRIMARY_COOLDOWN 0.2f

typedef struct player_input {
    float rotation;
    float thrust; // 0.0f to 1.0f, just a choice in case I have time for gamepad support
    bool shoot_primary;
    bool shoot_secondary;
    float time_since_primary;
    float time_since_secondary;
} player_input;

extern bool player_shoot_primary;

player_input get_player_input(void);

entity* create_player(float x, float y);

void reset_player(entity *player);

void update_player(entity *player, player_input input, float dt);

void weapon_knockback_player(entity *player, float amount);

void wrap_player_on_screen(entity *player, int screen_width, int screen_height);

void draw_player(entity *player, Texture2D tex);