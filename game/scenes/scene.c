#include <raylib.h>
#include <stdio.h>
#include <math.h>

#include "scene.h"
#include "../game.h"
#include "../entities/basic_bullet.h"

#include "../entities/player.h"

#define MAX_ASTEROIDS 10
#define MAX_BULLETS 1000
#define ASTEROID_SPAWN_RATE 1.0f

static int asteroid_count = 0;
static float time_since_last_asteroid = 0.0f;
static int bullet_count = 0;

scene* scene_base_new(void)
{
    scene* s = calloc(1, sizeof(scene));
    return s;
}


void scene_render(scene* s, game *g)
{
    s->render(s, g);
}

void scene_update(scene* s)
{
	s->update(s);
}

void scene_free(scene* s) {
    s->free_scene(s);
}

void spawn_asteroid(scene *s, entity* player, float dt) {
    // spawn asteroids
    time_since_last_asteroid += dt;
    if (time_since_last_asteroid > ASTEROID_SPAWN_RATE) {
        time_since_last_asteroid = 0.0f;
        if (asteroid_count < MAX_ASTEROIDS) {
            // spawn asteroid
            asteroid_count++;
            float x = (float)GetRandomValue(0, SCREEN_WIDTH);
            float y = (float)GetRandomValue(0, SCREEN_HEIGHT);
            int side = GetRandomValue(0, 3);
            switch (side) {
                case 0: // top
                    x = (float)GetRandomValue(0, SCREEN_WIDTH);
                    y = -100.0f;
                    break;
                case 1: // right
                    x = SCREEN_WIDTH + 100.0f;
                    y = (float)GetRandomValue(0, SCREEN_HEIGHT);
                    break;
                case 2: // bottom
                    x = (float)GetRandomValue(0, SCREEN_WIDTH);
                    y = SCREEN_HEIGHT + 100.0f;
                    break;
                case 3: // left
                    x = -100.0f;
                    y = (float)GetRandomValue(0, SCREEN_HEIGHT);
                    break;
            }
            s->asteroids[asteroid_count-1] = create_entity(x, y);
            s->asteroids[asteroid_count-1].health = 5.0f; // TODO: define asteroid health somewhere
            // set asteroid velocity towards player
            float dx = player->x - s->asteroids[asteroid_count-1].x;
            float dy = player->y - s->asteroids[asteroid_count-1].y;
            float len = sqrtf(dx*dx + dy*dy);
            s->asteroids[asteroid_count-1].vx = dx / len * 50.0f;
            s->asteroids[asteroid_count-1].vy = dy / len * 50.0f;
        }
    }
}

void remove_entity(entity* entities, int idx, int *entity_count) {
    //printf("removing entity %d\n", idx);
    // remove asteroid by moving the last asteroid to this position and decrementing the asteroid count
    entities[idx] = entities[*entity_count-1];
    *entity_count = *entity_count - 1;
}

static inline bool is_outside_screen(entity e) {
    const float margin = 100.0f;
    return e.x < -margin || e.x > SCREEN_WIDTH + margin || e.y < -margin || e.y > SCREEN_HEIGHT + margin;
}

// Remove offscreen and dead entities
void remove_entitites(scene *s) {
    // TODO: there's probably a bug when multiple objects need to be removed
    for (int i = 0; i < asteroid_count; i++) {
        if (is_outside_screen(s->asteroids[i])) {
            remove_entity(s->asteroids, i, &asteroid_count);
            continue;
        }
        if (s->asteroids[i].health <= 0.0f) {
            remove_entity(s->asteroids, i, &asteroid_count);
        }
    }
    for (int i = 0; i < bullet_count; i++) {
        if (is_outside_screen(s->projectiles[i])) {
            remove_entity(s->projectiles, i, &bullet_count);
            continue;
        }
        if (s->projectiles[i].health <= 0.0f) {
            remove_entity(s->projectiles, i, &bullet_count);
        }
    }
}

void scene_check_collisions(scene *s, entity *player) {
    for (int i = 0; i < asteroid_count; i++) {
        if (CheckCollisionCircles((Vector2){player->x, player->y}, PLAYER_COLLIDER_SIZE, (Vector2){s->asteroids[i].x, s->asteroids[i].y}, 20.0f)) {
            //printf("player hit by asteroid %d\n", i);
            player->health -= ASTEROID_COLLISION_DAMAGE;
            s->asteroids[i].health -= ASTEROID_COLLISION_DAMAGE;
        }
        for (int j = 0; j < bullet_count; j++) {
            if (CheckCollisionCircles((Vector2){s->asteroids[i].x, s->asteroids[i].y}, 20.0f, (Vector2){s->projectiles[j].x, s->projectiles[j].y}, BASIC_BULLET_SIZE)) {
                //printf("Bullet hit asteroid\n");
                s->asteroids[i].health -= BASIC_BULLET_DAMAGE;
                s->projectiles[j].health = -1.0f;
            }
        }
    }
}

void spawn_bullet(scene *s, entity* player) {
    // TODO: Spawn bullet projectiles here according to players primary weapon
    if (bullet_count >= MAX_BULLETS) {
        printf("CANNOT CREATE BULLET, BULLETS MAXED!");
        // TODO: instead just destroy the oldest bullet if needed
        return;
    }
    bullet_count++;
    entity bullet = create_basic_bullet(player->x, player->y, player->rotation);
    s->projectiles[bullet_count-1] = bullet;
    // knockback to player..
    weapon_knockback_player(player, BASIC_BULLET_KNOCKBACK);
}

void scene_update_testing(scene *s)
{
    if (s->current_state == GAME_STATE_GAME_OVER) {
        if (IsKeyPressed(KEY_R)) {
            scene_reset_testing(s);
            s->current_state = GAME_STATE_PLAYING;
        }
        return;
    }

    if (s->current_state == GAME_STATE_PAUSED) {
        // TODO: implement pause menu logic

        return;
    }

    entity* player = s->player;
    float dt = 1.0f / 60.0f;
    update_player(player, get_player_input(), dt);
    wrap_player_on_screen(player, SCREEN_WIDTH, SCREEN_HEIGHT);

    // update asteroids
    for (int i = 0; i < asteroid_count; i++) {
        update_entity(&s->asteroids[i], dt);
    }

    // update bullet_basic
    for (int i = 0; i < bullet_count; i++) {
        update_entity(&s->projectiles[i], dt);
    }

    // check for collisions, between player and asteroids and between projectiles and asteroids
    scene_check_collisions(s, player);
    

    spawn_asteroid(s, player, dt);

    if (player_shoot_primary)
        spawn_bullet(s, player);

    // If an asteroid is outside of the screen and outside spawn area, remove it
    remove_entitites(s);

    if (player->health <= 0.0) {
        printf("PLAYER IS DEAD!\n");
        s->current_state = GAME_STATE_GAME_OVER;
    }
}

void scene_render_testing(scene *s, game *g)
{
    draw_player(s->player, g->tm->player_tex);

    // draw asteroids
    for (int i = 0; i < asteroid_count; i++) {
        draw_entity_color(&s->asteroids[i], g->tm->meteor_tex, ASTEROID_COLOR);
    }

    // draw projectiles
    for (int i = 0; i < bullet_count; i++) {
        draw_entity(&s->projectiles[i], g->tm->bullet_tex);
    }

    if (s->current_state == GAME_STATE_GAME_OVER) {
        DrawText("GAME OVER\n Press 'R' to restart", 100, 100, 20, RED);
    }
}

scene* scene_init_testing(void) {
    scene* base = scene_base_new();
    base->player = create_player(SCREEN_WIDTH / 2.0f - 32.0f, SCREEN_HEIGHT / 2.0f - 32.0f);
    base->enter = NULL;
    base->exit = NULL;
    base->update = scene_update_testing;
    base->render = scene_render_testing;
    base->free_scene = scene_free_testing;
    base->next = NULL;
    base->previous = NULL;
    base->asteroids = malloc(sizeof(entity)*MAX_ASTEROIDS);
    base->projectiles = malloc(sizeof(entity)*MAX_BULLETS);
    base->current_state = GAME_STATE_PLAYING;
    return base;
}

void scene_reset_testing(scene *s) {
    reset_player(s->player);
    asteroid_count = 0;
    bullet_count = 0;
    time_since_last_asteroid = 0.0f;
}

void scene_free_testing(scene* s) {
    printf("freeing testing scene...\n");
    printf("freeing player...\n");
    free(s->player);
    free(s);
}
