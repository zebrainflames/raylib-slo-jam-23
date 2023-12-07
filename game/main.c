#include "raylib.h"

#include "game/game.h"

#if defined(PLATFORM_WEB) || defined(EMSCRIPTEN)
#include <emscripten.h>
#endif

static game g;

void main_loop()
{
    game_get_input(&g);
    game_update(&g);
    game_draw(&g);
}

int main()
{
    game_init(&g);
    
#if defined(PLATFORM_WEB) || defined(EMSCRIPTEN)
    emscripten_set_main_loop(main_loop, 0, 1);
#else
    while (!game_window_should_close(&g))
    {
        main_loop();
    }
#endif

    game_quit(&g);
    return 0;
}
