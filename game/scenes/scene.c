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

void scene_free(scene* s) {
    s->free_scene(s);
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
    draw_player(player, g->tm->player_tex);
}

scene* scene_init_testing(void) {
    scene_testing* st = malloc(sizeof(scene_testing)); 
    scene* base = scene_base_new();
    st->base = base;
    //s->base = base_scene;
    base->player = (entity*)calloc(1, sizeof(entity));
    if (base->player == NULL)
	{
		fprintf(stderr, "FAILED TO ALLOCATE MEMORY FOR PLAYER!\n");
		exit(EXIT_FAILURE);
	}
    base->player->x = 200;
    base->player->y = 200;
    base->player->scale = 0.125f;
    base->enter = NULL;
    base->exit = NULL;
    base->update = scene_update_testing;
    base->render = scene_render_testing;
    base->free_scene = scene_free_testing;
    base->next = NULL;
    base->previous = NULL;
    base->parent = st;
    return base;
}

void scene_free_testing(scene* s) {
    printf("freeing testing scene...\n");
    if (s->parent != NULL) {
        printf("freeing parent...\n");
        scene_testing* st = (scene_testing*)s->parent;
        free(st); // <<-- what happens if we free parent first? do we get a dangling pointer?
        // NOTE: here we'd free any other resources associated with the scene allocted in st directly
        
    }
    printf("freeing player...\n");
    free(s->player);
    printf("freeing base...\n");
    free(s);

}
