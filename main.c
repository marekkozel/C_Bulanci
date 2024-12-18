#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include "Config/sdl.h"
#include "player.h"
#include "keybinds.h"
#include "Scenes/Obstacles/obstacles.h"

#define WINDOW_WIDTH (1920)
#define WINDOW_HEIGHT (1080)

int main()
{
    double seconds_timer = 0;
    double delta_timer = 0;
    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;
    double deltaTime = 0;

    SDL_Context window = sdl_window_setup();

    // World section
    SDL_Texture *background_text = IMG_LoadTexture(window.renderer, "/home/marek/C_Bulanci/Assets/background.png");
    if (!background_text)
    {
        printf("error creating texture: %s\n", SDL_GetError());
        sdl_context_free(&window);
        return;
    }
    SDL_Rect background_rect;
    SDL_QueryTexture(background_text, NULL, NULL, &background_rect.w, &background_rect.h);
    background_rect.x = 0;
    background_rect.y = 0;
    // background_rect.w *= 1.5;
    // background_rect.h *= 1.5;

    Obstacles obstacles;
    init_obstacles(&obstacles, 1);
    set_obstacles(&obstacles, &window);

    // player section
    Players players;
    init_players(&players);

    Player player1;
    init_player(&player1, &window, 0, "/home/marek/C_Bulanci/Assets/Player/blue_bulanek_down.png");

    add_player(&players, &player1);

    Player player2;
    init_player(&player2, &window, 1, "/home/marek/C_Bulanci/Assets/Player/red_bulanek_up.png");

    add_player(&players, &player2);

    Player player3;
    init_player(&player3, &window, 2, "/home/marek/C_Bulanci/Assets/Player/green_bulanek_down.png");

    add_player(&players, &player3);

    Player player4;
    init_player(&player4, &window, 3, "/home/marek/C_Bulanci/Assets/Player/orange_bulanek_down.png");

    add_player(&players, &player4);

    int *close_request = (int *)malloc(sizeof(int));
    *close_request = 0;

    while (!*close_request)
    {
        seconds_timer = delta_timer * deltaTime;

        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();

        deltaTime = (double)((NOW - LAST) / (double)SDL_GetPerformanceFrequency());

        SDL_RenderClear(window.renderer);

        SDL_RenderCopy(window.renderer, background_text, NULL, &background_rect);

        read_keys(close_request, &window, &players);

        for (int i = 0; i < players.count_players; i++)
        {
            move_player(&players.players[i], deltaTime, &players, &obstacles);

            SDL_RenderCopy(window.renderer, players.players[i].texture, NULL, players.players[i].rectangle);
        }

        for (int i = 0; i < obstacles.count_obstacles; i++)
        {
            SDL_RenderCopy(window.renderer, obstacles.obstacles[i].texture, NULL, obstacles.obstacles[i].rectangle);
        }

        SDL_RenderPresent(window.renderer);

        delta_timer++;
    }

    sdl_context_free(&window);

    return 0;
}