#include <stdio.h>

#include "scene.h"



scene* scene_base_new(void)
{
    scene* s = calloc(1, sizeof(scene));
    return s;
}


void scene_update_testing(void)
{
    printf("would do an update tick here...\n");
}

void scene_render_testing(void)
{
}

void scene_init_testing(scene_testing* s)
{
    *s = (scene_testing){0}; 
    scene* base_scene = scene_base_new();
    
    s->base = base_scene;
    s->base->enter = NULL;
    s->base->exit = NULL;
    s->base->update = scene_update_testing;
    s->base->render = scene_render_testing;
    s->base->next_scene = NULL;
    s->base->previous_scene = NULL;
    s->tx = 0;
    s->ty = 0;
    s->ix = 0;
    s->iy = 0;

}

void scene_free_testing(scene_testing* s)
{
    // TODO: is this clean enough...?
    free(s->base); // TODO: implement a cleaning func for scene_base to make it easier to free all resources later...
}
