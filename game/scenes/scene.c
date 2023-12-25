#include <raylib.h>
#include <stdio.h>
#include <math.h>

#include "scene.h"
#include "../game.h"

#include "../entities/player.h"

#define MAX_ASTEROIDS 10
#define ASTEROID_SPAWN_RATE 1.0f

static int asteroid_count = 0;
static float time_since_last_asteroid = 0.0f;

scene* scene_base_new(void)
{
    scene* s = calloc(1, sizeof(scene));
    // remember to init everything, now all is null :-D
    return s;
}


void scene_render(scene* s, void* g)
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

void scene_update_testing(scene *s)
{

    entity* player = s->player;
    float dt = 1.0f / 60.0f;
    update_player(player, get_player_input(), dt);
    wrap_player_on_screen(player, SCREEN_WIDTH, SCREEN_HEIGHT);

    // update asteroids
    for (int i = 0; i < asteroid_count; i++) {
        update_entity(&s->asteroids[i], dt);
    }

    // check for collisions, between player and asteroids and between projectiles and asteroids
    for (int i = 0; i < asteroid_count; i++) {
        if (CheckCollisionCircles((Vector2){player->x, player->y}, PLAYER_COLLIDER_SIZE, (Vector2){s->asteroids[i].x, s->asteroids[i].y}, 20.0f)) {
            printf("player hit by asteroid %d\n", i);
        }
    }

    // If an asteroid is outside of the screen, remove it
    for (int i = 0; i < asteroid_count; i++) {
        if (s->asteroids[i].x < -100.0f || s->asteroids[i].x > SCREEN_WIDTH + 100.0f || s->asteroids[i].y < -100.0f || s->asteroids[i].y > SCREEN_HEIGHT + 100.0f) {
            printf("removing asteroid %d\n", i);
            // remove asteroid by moving the last asteroid to this position and decrementing the asteroid count
            s->asteroids[i] = s->asteroids[asteroid_count-1];
            asteroid_count--;
        }
    }

    // spawn asteroids
    time_since_last_asteroid += dt;
    if (time_since_last_asteroid > ASTEROID_SPAWN_RATE) {
        time_since_last_asteroid = 0.0f;
        if (asteroid_count < MAX_ASTEROIDS) {
            // spawn asteroid
            asteroid_count++;
            printf("spawning asteroid %d\n", asteroid_count);
            // TODO: note that this will either break or we have to make sure we
            // remove destroyed asteroids from the array whenever that happens
            // let's go with the latter for now
            // get start pos randomly outside of screen
            // TODO: move to a separate header file to avoid cluttering this file
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
            // set asteroid velocity towards player
            float dx = player->x - s->asteroids[asteroid_count-1].x;
            float dy = player->y - s->asteroids[asteroid_count-1].y;
            float len = sqrtf(dx*dx + dy*dy);
            s->asteroids[asteroid_count-1].vx = dx / len * 50.0f;
            s->asteroids[asteroid_count-1].vy = dy / len * 50.0f;
        }
    }
}

void scene_render_testing(scene *s, void* data)
{
    // cast to game* to get access to the texture manager
    game* g = (game*)data;
	//printf("would do a render tick here...\n");
    draw_player(s->player, g->tm->player_tex);

    // draw asteroids
    for (int i = 0; i < asteroid_count; i++) {
        draw_entity(&s->asteroids[i], g->tm->meteor_tex);
    }

}

scene* scene_init_testing(void) {
    scene_testing* st = malloc(sizeof(scene_testing)); 
    scene* base = scene_base_new();
    st->base = base;
    base->player = create_player(200.0f, 200.0f);
    printf("player->scale after creation: %f\n", base->player->scale);
    base->enter = NULL;
    base->exit = NULL;
    base->update = scene_update_testing;
    base->render = scene_render_testing;
    base->free_scene = scene_free_testing;
    base->next = NULL;
    base->previous = NULL;
    base->parent = st;
    base->asteroids = malloc(sizeof(entity)*MAX_ASTEROIDS);
    return base;
}

void scene_free_testing(scene* s) {
    printf("freeing testing scene...\n");
    if (s->parent != NULL) {
        printf("freeing parent...\n");
        scene_testing* st = (scene_testing*)s->parent;
        free(st);
    }
    printf("freeing player...\n");
    free(s->player);
    printf("freeing base...\n");
    free(s);

}
