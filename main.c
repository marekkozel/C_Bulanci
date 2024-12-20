#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>
#include <assert.h>
#include "Config/sdl.h"
#include "player.h"
#include "keybinds.h"
#include "Scenes/Obstacles/obstacles.h"
#include "Config/dynamic_array.h"
#include "Weapons/Power_ups/power_ups.h"
#include "Weapons/Projectils/projectils.h"

#define WINDOW_WIDTH (1920)
#define WINDOW_HEIGHT (1080)

int main()
{
    srand(time(NULL));

    int seconds_timer = 1;
    double delta_timer = 1;
    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;
    double miliseconds_time = 0;
    double deltaTime = 0;

    SDL_Context window = sdl_window_setup();

    // World section
    SDL_Texture *background_text = IMG_LoadTexture(window.renderer, "../Assets/background.png");
    assert(background_text);

    SDL_Rect background_rect;
    SDL_QueryTexture(background_text, NULL, NULL, &background_rect.w, &background_rect.h);
    background_rect.x = 0;
    background_rect.y = 0;

    Obstacles obstacles;
    init_obstacles(&obstacles, 1);
    set_obstacles(&obstacles, &window);

    // player section
    Players players;
    init_players(&players);

    char player_path[500] = "../Assets/Player/";

    Player player1;
    init_player(&player1, &window, 0, player_path, RED);

    add_player(&players, &player1);

    Player player2;
    init_player(&player2, &window, 1, player_path, GREEN);

    add_player(&players, &player2);

    // Player player3;
    // init_player(&player3, &window, 2, player_path, BLUE);

    // add_player(&players, &player3);

    // Player player4;
    // init_player(&player4, &window, 3, player_path, ORANGE);

    // add_player(&players, &player4);

    // Power_up section
    dynarray power_ups;
    init_power_ups(&power_ups);

    // Projectils
    dynarray projectils;
    init_projectils(&projectils);

    // Font

    int *close_request = (int *)malloc(sizeof(int));
    *close_request = 0;

    while (!*close_request)
    {
        if (round(miliseconds_time) - 1 == seconds_timer)
        {
            spawn_power_up(&power_ups, &window, seconds_timer);

            seconds_timer++;
        }

        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();

        uint32_t startTime = SDL_GetTicks();

        deltaTime = (double)((NOW - LAST) / (double)SDL_GetPerformanceFrequency());

        SDL_RenderClear(window.renderer);

        SDL_RenderCopy(window.renderer, background_text, NULL, &background_rect);

        read_keys(close_request, &window, &players, &projectils, miliseconds_time);

        for (int i = 0; i < players.count_players; i++)
        {
            animate_player(&players.players[i], &window, player_path);
            move_player(&players.players[i], deltaTime, &players, &obstacles, &power_ups, &projectils, miliseconds_time);

            SDL_RenderCopy(window.renderer, players.players[i].texture, NULL, players.players[i].rectangle);
        }

        for (int i = 0; i < obstacles.count_obstacles; i++)
        {
            SDL_RenderCopy(window.renderer, obstacles.obstacles[i].texture, NULL, obstacles.obstacles[i].rectangle);
        }

        for (int i = 0; i < power_ups.size; i++)
        {
            Power_up *power_up;
            power_up = dynarray_get(&power_ups, i);
            SDL_RenderCopy(window.renderer, power_up->texture, NULL, power_up->rectangle);
        }

        for (int i = 0; i < projectils.size; i++)
        {
            Projectil *projectil;
            projectil = dynarray_get(&projectils, i);
            move_projectil(projectil, deltaTime);
            SDL_RenderCopy(window.renderer, projectil->texture, NULL, projectil->rectangle);
            projectil_collision(&projectils, &obstacles, projectil);
            destruct_projectil(&projectils, projectil, miliseconds_time);
        }

        // SDL_RenderCopy(window.renderer, Message, NULL, &Message_rect);

        SDL_RenderPresent(window.renderer);

        uint32_t currTime = SDL_GetTicks();

        miliseconds_time += (currTime - startTime) / 1000.0; // Convert to seconds.
    }

    // SDL_FreeSurface(surfaceMessage);
    // SDL_DestroyTexture(Message);
    sdl_context_free(&window);

    return 0;
}

void drawText(SDL_Surface *screen, char *string,
              int size, int x, int y,
              int fR, int fG, int fB,
              int bR, int bG, int bB)
{

    TTF_Font *font = TTF_OpenFont("ARIAL.TTF", size);

    SDL_Color foregroundColor = {fR, fG, fB};
    SDL_Color backgroundColor = {bR, bG, bB};

    SDL_Surface *textSurface = TTF_RenderText_Shaded(font, string, foregroundColor, backgroundColor);

    SDL_Rect textLocation = {x, y, 0, 0};

    SDL_BlitSurface(textSurface, NULL, screen, &textLocation);

    SDL_FreeSurface(textSurface);

    TTF_CloseFont(font);
}