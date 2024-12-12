#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include "Config/sdl.h"
#include "Player/player.h"
#include "Config/keybinds.h"

int main()
{

    SDL_Context window = sdl_window_setup();

    Players *players;
    init_players(players);

    Player player;
    init_player(&player, &window, 0);

    add_player(players, &player);

    int *close_request = (int *)malloc(sizeof(int));
    *close_request = 0;

    while (!*close_request)
    {

        // SDL_Event event;
        // while (SDL_PollEvent(&event))
        // {

        //     switch (event.type)
        //     {
        //     case SDL_QUIT:
        //     {
        //         *close_request = 1;
        //         break;
        //     }
        //     }
        // }
        // // SDL_RenderClear(window.renderer);

        // SDL_RenderCopy(window.renderer, players->players[0].texture, NULL, players->players[0].rectangle);
        // SDL_RenderPresent(window.renderer);

        read_keys(close_request, &window, players);

        SDL_RenderPresent(window.renderer);

        SDL_Delay(1000 / 60);
    }

    SDL_DestroyRenderer(window.renderer);
    SDL_DestroyWindow(window.window);
    SDL_Quit();
    sdl_context_free(&window);

    return 0;
}