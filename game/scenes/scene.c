#include <raylib.h>
#include <stdio.h>

#include "scene.h"
#include "../game.h"

#include "../entities/player.h"


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

void scene_update_testing(scene *s)
{

    entity* player = s->player;
    float dt = 1.0f / 60.0f;
    update_player(player, get_player_input(), dt);
    wrap_player_on_screen(player, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void scene_render_testing(scene *s, void* data)
{
    // cast to game* to get access to the texture manager
    game* g = (game*)data;
	//printf("would do a render tick here...\n");
	//scene* s = (scene*)data;
    entity* player = s->player;
    draw_entity(player, g->tm->player_tex);
}

void scene_init_testing(scene_testing* s) {
    *s = (scene_testing){0}; 
    scene* base_scene = scene_base_new();
    
    s->base = base_scene;
    s->base->player = (entity*)calloc(1, sizeof(entity));
    if (s->base->player == NULL)
	{
		fprintf(stderr, "FAILED TO ALLOCATE MEMORY FOR PLAYER!\n");
		exit(EXIT_FAILURE);
	}
    s->base->player->x = 200;
    s->base->player->y = 200;
    s->base->player->scale = 0.5f;
    s->base->enter = NULL;
    s->base->exit = NULL;
    s->base->update = scene_update_testing;
    s->base->render = scene_render_testing;
    s->base->next = NULL;
    s->base->previous = NULL;
}

void scene_free_testing(scene_testing* s) {
    // TODO: is this clean enough...?
    free(s->base->player);
    free(s->base); // TODO: implement a cleaning func for scene_base to make it easier to free all resources later...
}
