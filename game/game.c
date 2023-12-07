#include "game.h"

#define UPDATE_FPS 60
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define UPDATE_FPS 60

int game_window_should_close(game *g) {
    return WindowShouldClose() || g->should_quit;
}

void game_init(game *g) {
    *g = (game){0};
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game shell");
    InitAudioDevice();
    g->scene = 0;

    SetTargetFPS(UPDATE_FPS);
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
    g->tx += g->ix;
    g->ty += g->iy;
}

void game_draw(game *g) {
    ClearBackground(BLACK);
    BeginDrawing();
    DrawFPS(10, 10);

    DrawText("Testing", g->tx, g->ty, 20, RAYWHITE);
    EndDrawing();
}

void game_quit(game *g) {
    // freeing resources, from asset managers, etc.
    g->should_quit = 1; // Noop thing to avoid warnings here for now...
    // Raylib cleanup and closing functions..
    CloseAudioDevice();
    CloseWindow();
}