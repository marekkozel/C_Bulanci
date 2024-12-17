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

#define WINDOW_WIDTH (1920)
#define WINDOW_HEIGHT (1080)

int main()
{
    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;
    double deltaTime = 0;

    SDL_Context window = sdl_window_setup();

    Players players;
    init_players(&players);

    SDL_Texture *tex_orange = IMG_LoadTexture(window.renderer, "/home/marek/C_Bulanci/Player/orange_bulanek.png");
    if (!tex_orange)
    {
        printf("error creating texture: %s\n", SDL_GetError());
        sdl_context_free(&window);
        return;
    }
    SDL_Texture *tex_green = IMG_LoadTexture(window.renderer, "/home/marek/C_Bulanci/Player/green_bulanek.png");
    if (!tex_green)
    {
        printf("error creating texture: %s\n", SDL_GetError());
        sdl_context_free(&window);
        return;
    }

    Player player1;
    init_player(&player1, &window, 0, tex_green);

    add_player(&players, &player1);

    Player player2;
    init_player(&player2, &window, 1, tex_orange);

    add_player(&players, &player2);

    int *close_request = (int *)malloc(sizeof(int));
    *close_request = 0;

    while (!*close_request)
    {
        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();

        deltaTime = (double)((NOW - LAST) / (double)SDL_GetPerformanceFrequency());

        SDL_RenderClear(window.renderer);

        read_keys(close_request, &window, &players);

        for (int i = 0; i < players.count_players; i++)
        {
            move_player(&players.players[i], deltaTime, &players);

            SDL_RenderCopy(window.renderer, players.players[i].texture, NULL, players.players[i].rectangle);
        }

        SDL_RenderPresent(window.renderer);
    }

    sdl_context_free(&window);

    return 0;
}