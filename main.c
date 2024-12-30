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
#include "Scenes/Main_menu/main_menu.h"
#include "Scenes/Leaderboard/leaderboard.h"
#include "Player/bot.h"
#include "Sounds/sounds.h"

#define WINDOW_WIDTH (1920)
#define WINDOW_HEIGHT (1080)

int main()
{
    srand(time(NULL));

    // how long should this game be:
    int sec = 90;

    int m = 0;
    int s = 0;
    int seconds_timer = 1;
    double delta_timer = 1;
    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;
    double miliseconds_time = 0;
    double deltaTime = 0;

    int first_player = 0;
    bool player_exist = false;

    SDL_Context window = sdl_window_setup();

    int *close_request = (int *)malloc(sizeof(int));
    *close_request = 0;

    // player section
    Players players;
    init_players(&players);

    char player_path[500] = "../Assets/Player/";

    // Font
    TTF_Init();
    TTF_Font *font = TTF_OpenFont("../Assets/Fonts/Venite.ttf", 45);
    assert(font);
    TTF_Font *main_font = TTF_OpenFont("../Assets/Fonts/Venite.ttf", 64);
    assert(font);

    char score_text[100] = "Score: 0";
    char time_text[100] = "01:30";

    SDL_Color RGB_WHITE = {255, 255, 255};

    // Main menu
    start_main_menu(&players, &window, close_request, font, main_font);

    // World section
    SDL_Texture *background_text = IMG_LoadTexture(window.renderer, "../Assets/background.png");
    assert(background_text);

    SDL_Rect background_rect;
    SDL_QueryTexture(background_text, NULL, NULL, &background_rect.w, &background_rect.h);
    background_rect.x = 0;
    background_rect.y = 0;

    Obstacles obstacles;
    init_obstacles(&obstacles, 6);
    set_obstacles(&obstacles, &window);

    // Power_up section
    dynarray power_ups;
    init_power_ups(&power_ups);

    // Projectils
    dynarray projectils;
    init_projectils(&projectils);

    SDL_Surface *score_surface;
    SDL_Texture *score_texture;

    SDL_Surface *time_surface = TTF_RenderText_Solid(font, time_text, RGB_WHITE);
    SDL_Texture *time_texture = SDL_CreateTextureFromSurface(window.renderer, time_surface);

    while (!*close_request)
    {
        SDL_RenderClear(window.renderer);
        SDL_RenderCopy(window.renderer, background_text, NULL, &background_rect);

        if (round(miliseconds_time) - 1 == seconds_timer)
        {
            play_sound();
            spawn_power_up(&power_ups, &window, seconds_timer);

            seconds_timer++;

            m = floor(((sec - seconds_timer + 1)) / 60);
            s = ((sec - seconds_timer + 1) - (m * 60));

            sprintf(time_text, "%02d:%02d", m, s);
            SDL_FreeSurface(time_surface);
            SDL_DestroyTexture(time_texture);

            time_surface = TTF_RenderText_Solid(font, time_text, RGB_WHITE);
            time_texture = SDL_CreateTextureFromSurface(window.renderer, time_surface);

            if (sec - seconds_timer + 2 <= 0)
            {
                int max_score_index = 0;
                int max_score = 0;
                for (int i = 0; i < players.count_players; i++)
                {
                    if (get_player_score(&players.players[i]) > max_score)
                    {
                        max_score_index = i;
                        max_score = get_player_score(&players.players[i]);
                    }
                }
                username_input_screen(&window, close_request, font, main_font, &players.players[max_score_index]);
                *close_request = 1;
                leaderboard(&window, close_request, font, main_font);
            }
        }

        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();

        uint32_t startTime = SDL_GetTicks();

        deltaTime = (double)((NOW - LAST) / (double)SDL_GetPerformanceFrequency());

        read_keys(close_request, &window, &players, &projectils, miliseconds_time);

        // Obstacles render
        for (int i = 0; i < obstacles.count_obstacles; i++)
        {
            SDL_RenderCopy(window.renderer, obstacles.obstacles[i].texture, NULL, obstacles.obstacles[i].rectangle);
        }

        // Power_ups render
        for (int i = 0; i < power_ups.size; i++)
        {
            Power_up *power_up;
            power_up = dynarray_get(&power_ups, i);
            SDL_RenderCopy(window.renderer, power_up->texture, NULL, power_up->rectangle);
        }

        // Exist player
        for (int i = 0; i < players.count_players; i++)
        {
            if (players.players[i].type == 0)
            {
                player_exist = true;
            }
        }

        // Projectils render
        for (int i = 0; i < projectils.size; i++)
        {
            Projectil *projectil;
            projectil = dynarray_get(&projectils, i);
            move_projectil(projectil, deltaTime);
            SDL_RenderCopy(window.renderer, projectil->texture, NULL, projectil->rectangle);
            projectil_collision(&projectils, &obstacles, projectil, &window, player_exist, miliseconds_time);

            destroy_projectil(&projectils, projectil, miliseconds_time);
        }

        first_player = 0;

        // Player render
        for (int i = 0; i < players.count_players; i++)
        {
            animate_player(&players.players[i], &window, player_path);
            move_player(&players.players[i], deltaTime, &players, &obstacles, &power_ups, &projectils, &window, miliseconds_time);

            SDL_RenderCopy(window.renderer, players.players[i].texture, NULL, &players.players[i].rectangle);

            // Score render
            if (get_player_type(&players.players[i]) == 0)
            {
                sprintf(score_text, "Score : %d", get_player_score(&players.players[i]));

                score_surface = TTF_RenderText_Solid(font, score_text, RGB_WHITE);
                score_texture = SDL_CreateTextureFromSurface(window.renderer, score_surface);

                if (first_player == 0)
                {
                    SDL_Rect score_rect0 = {.x = 50, .y = 40, score_surface->w, score_surface->h};
                    SDL_RenderCopy(window.renderer, score_texture, NULL, &score_rect0);
                    first_player = 1;
                }
                else if (first_player == 1)
                {
                    SDL_Rect score_rect1 = {.x = WINDOW_WIDTH - score_surface->w - 50, .y = 40, score_surface->w, score_surface->h};
                    SDL_RenderCopy(window.renderer, score_texture, NULL, &score_rect1);
                }

                SDL_FreeSurface(score_surface);
                SDL_DestroyTexture(score_texture);
            }

            if (get_player_type(&players.players[i]) == 1)
            {
                bot_logic(&players, &players.players[i], &window, &projectils, &power_ups, &obstacles, miliseconds_time);
            }
        }

        // Time render
        SDL_Rect time_rect = {.x = WINDOW_WIDTH / 2 - time_surface->w / 2, .y = 40, time_surface->w, time_surface->h};
        SDL_RenderCopy(window.renderer, time_texture, NULL, &time_rect);

        SDL_RenderPresent(window.renderer);

        uint32_t currTime = SDL_GetTicks();

        miliseconds_time += (currTime - startTime) / 1000.0; // Convert to seconds.
    }

    TTF_CloseFont(font);
    TTF_CloseFont(main_font);
    TTF_Quit();
    SDL_DestroyRenderer(window.renderer);
    SDL_DestroyWindow(window.window);

    SDL_Quit();

    return 0;
}