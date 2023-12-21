#include "game.h"
#include "scenes/scene.h"
#include "stdio.h"

int game_window_should_close(game *g) {
    return WindowShouldClose() || g->should_quit;
}

void game_init(game *g) {
    *g = (game){0};
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game shell");
    InitAudioDevice();
    g->scene = 0;
    scene_testing testing_scene;
    scene_init_testing(&testing_scene);
    g->current_scene = testing_scene.base;
    // initialize scene array
    g->scene_amount = 1;
    g->scenes = malloc(g->scene_amount * sizeof(scene*));
    if (g->scenes == NULL)
    {
        fprintf(stderr, "FAILED TO ALLOCATE MEMORY FOR SCENES!\n");
        exit(EXIT_FAILURE);
    }
    g->scenes[0] = g->current_scene; 

    SetTargetFPS(UPDATE_FPS);

    // load assets
    g->tm = texture_manager_init();
}

void game_get_input(game *g) {
    int ix = 0;
    int iy = 0;
    if (IsKeyPressed(KEY_LEFT)) ix--;
    if (IsKeyPressed(KEY_RIGHT)) ix++;
    if (IsKeyPressed(KEY_UP)) iy--;
    if (IsKeyPressed(KEY_DOWN)) iy++;
    g->ix = ix;
    g->iy = iy;
}

void game_update(game *g) {
    //g->current_scene->update(g->current_scene);
    scene_update(g->current_scene);
}

void game_draw(game *g) {
    ClearBackground(BLACK);
    BeginDrawing();
    DrawFPS(10, 10);

    // TODO: why doesn't this compile if game is passed strongly typed?
    scene_render(g->current_scene, (void*)g);


    EndDrawing();
}

void game_quit(game *g) {
    // freeing resources, from asset managers, etc.
    texture_manager_free(g->tm);
    // audio_manager_free(g->am);
    // free all scenes, safely
    for (int i = 0; i < g->scene_amount; i++)
    {
        free(g->scenes[i]);
    }

    // Raylib cleanup and closing functions..
    CloseAudioDevice();
    CloseWindow();
}