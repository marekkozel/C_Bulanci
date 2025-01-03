
#include "keybinds.h"

void read_keys(int *close_request, SDL_Context *window, Players *players, dynarray *projectils, double timer)
{
    // Initilize 2 players, controled by human
    int first_player = 0;
    Player *player1 = malloc(sizeof(Player));
    Player *player2 = malloc(sizeof(Player));
    for (int i = 0; i < players->count_players; i++)
    {
        Player *player = &players->players[i];
        if (get_player_type(player) == 0 && first_player == 0)
        {
            player1 = player;
            first_player = 1;
        }
        else if (get_player_type(player) == 0 && first_player == 1)
        {
            player2 = player;
        }
    }

    SDL_Event event;

    while (SDL_PollEvent(&event))
    {

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
                // Set just one direction velocity, and set friction in the other one, so player can move only in 4 directions.
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
                spawn_projectil(player1, projectils, window, timer);

                break;
            case SDL_SCANCODE_KP_0:
                spawn_projectil(player2, projectils, window, timer);

                break;
            case SDL_SCANCODE_RCTRL:
                spawn_projectil(player2, projectils, window, timer);
                break;
            default:
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
            default:
                break;
            }
            break;
        }
        default:
            break;
        }
    }
}
