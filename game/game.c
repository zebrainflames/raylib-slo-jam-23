#include "game.h"
#include "scenes/scene.h"
#include "stdio.h"

int game_window_should_close(game *g) {
    return WindowShouldClose() || g->should_quit;
}

void game_add_scene(game *g, scene* (*init_scene)(void)) {
    g->scene_amount++;
    g->scenes = realloc(g->scenes, g->scene_amount * sizeof(scene*));
    if (g->scenes == NULL)
    {
        fprintf(stderr, "FAILED TO ALLOCATE MEMORY FOR SCENES!\n");
        exit(EXIT_FAILURE);
    }
    scene* new_scene = init_scene();
    g->scenes[g->scene_amount - 1] = new_scene;
    g->current_scene = new_scene;
}

void game_init(game *g) {
    *g = (game){0};
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game shell");
    InitAudioDevice();
    
    game_add_scene(g, scene_init_testing);
    
    SetTargetFPS(UPDATE_FPS);

    // load assets
    g->tm = texture_manager_init();
}

void game_update(game *g) {
    scene_update(g->current_scene);
}

void game_draw(game *g) {
    ClearBackground(BLACK);
    BeginDrawing();
    scene_render(g->current_scene, g);
    EndDrawing();
}

void game_quit(game *g) {
    // freeing resources, from asset managers, etc.
    texture_manager_free(g->tm);
    // audio_manager_free(g->am);
    // free all scenes, safely
    for (int i = 0; i < g->scene_amount; i++)
    {
        scene_free(g->scenes[i]);
    }

    // Raylib cleanup and closing functions..
    CloseAudioDevice();
    CloseWindow();
}