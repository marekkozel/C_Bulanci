#pragma once

#include "sdl.h"
#include "Player/player.h"
#include "keybinds.h"

// typedef enum
// {
//     DOWN_W,
//     DOWN_A,
//     DOWN_S,
//     DOWN_D,
//     UP_W,
//     UP_A,
//     UP_S,
//     UP_D,
//     DOWN_UP,
//     DOWN_LEFT,
//     DOWN_DOWN,
//     DOWN_RIGHT,
//     UP_UP,
//     UP_LEFT,
//     UP_DOWN,
//     UP_RIGHT
// } KeyPressed;

void read_keys(int *close_request, SDL_Context *window, Players *players, dynarray *projectils)
{
    Player *player1 = &players->players[0];
    Player *player2 = &players->players[1];
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        // printf("%s", event.text);
        switch (event.type)
        {
        case SDL_QUIT:
        {
            *close_request = 1;
            return;
            break;
        }

        case SDL_KEYDOWN:
        {
            switch (event.key.keysym.scancode)
            {
            case SDL_SCANCODE_ESCAPE:
            {
                *close_request = 1;
                return;
                break;
            }
            case SDL_SCANCODE_W:
                set_player_friction_y(player1, 0);
                set_player_velovity_y(player1, -PLAYER_SPEED);
                set_player_friction_x(player1, FRICTION);
                set_player_direction(player1, 0, -1);

                break;
            case SDL_SCANCODE_UP:
                set_player_friction_y(player2, 0);
                set_player_velovity_y(player2, -PLAYER_SPEED);
                set_player_friction_x(player2, FRICTION);
                set_player_direction(player2, 0, -1);

                break;
            case SDL_SCANCODE_A:
                set_player_friction_x(player1, 0);
                set_player_velovity_x(player1, -PLAYER_SPEED);
                set_player_friction_y(player1, FRICTION);
                set_player_direction(player1, -1, 0);
                break;
            case SDL_SCANCODE_LEFT:
                set_player_friction_x(player2, 0);
                set_player_velovity_x(player2, -PLAYER_SPEED);
                set_player_friction_y(player2, FRICTION);
                set_player_direction(player2, -1, 0);
                break;
            case SDL_SCANCODE_S:
                set_player_friction_y(player1, 0);
                set_player_velovity_y(player1, PLAYER_SPEED);
                set_player_friction_x(player1, FRICTION);
                set_player_direction(player1, 0, 1);
                break;
            case SDL_SCANCODE_DOWN:
                set_player_friction_y(player2, 0);
                set_player_velovity_y(player2, PLAYER_SPEED);
                set_player_friction_x(player2, FRICTION);
                set_player_direction(player2, 0, 1);

                break;
            case SDL_SCANCODE_D:
                set_player_friction_x(player1, 0);
                set_player_velovity_x(player1, PLAYER_SPEED);
                set_player_friction_y(player1, FRICTION);
                set_player_direction(player1, 1, 0);

                break;
            case SDL_SCANCODE_RIGHT:
                set_player_friction_x(player2, 0);
                set_player_velovity_x(player2, PLAYER_SPEED);
                set_player_friction_y(player2, FRICTION);
                set_player_direction(player2, 1, 0);

                break;
            case SDL_SCANCODE_SPACE:
                spawn_projectil(player1, projectils, window);

                break;
            }
            break;
        }
        case SDL_KEYUP:
        {
            switch (event.key.keysym.scancode)
            {
            case SDL_SCANCODE_W:
                if (get_player_velocity_y(player1) < 0)
                {
                    set_player_friction_y(player1, FRICTION);
                }
                break;
            case SDL_SCANCODE_UP:
                if (get_player_velocity_y(player2) < 0)
                {
                    set_player_friction_y(player2, FRICTION);
                }
                break;
            case SDL_SCANCODE_A:
                if (get_player_velocity_x(player1) < 0)
                {
                    set_player_friction_x(player1, FRICTION);
                }
                break;
            case SDL_SCANCODE_LEFT:
                if (get_player_velocity_x(player2) < 0)
                {
                    set_player_friction_x(player2, FRICTION);
                }
                break;

            case SDL_SCANCODE_S:
                if (get_player_velocity_y(player1) > 0)
                {
                    set_player_friction_y(player1, FRICTION);
                }
                break;
            case SDL_SCANCODE_DOWN:
                if (get_player_velocity_y(player2) > 0)
                {
                    set_player_friction_y(player2, FRICTION);
                }
                break;
            case SDL_SCANCODE_D:
                if (get_player_velocity_x(player1) > 0)
                {
                    set_player_friction_x(player1, FRICTION);
                }
                break;
            case SDL_SCANCODE_RIGHT:
                if (get_player_velocity_x(player2) > 0)
                {
                    set_player_friction_x(player2, FRICTION);
                }
                break;
            }
            break;
        }
        }
    }
}
