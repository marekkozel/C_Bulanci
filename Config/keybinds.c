#pragma once

#include "sdl.h"
#include "Player/player.h"
#include "keybinds.h"

void read_keys(int *close_request, SDL_Context *window, Players *players)
{
    // Player *player = &players[0];
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
        }
    }
}

// case SDL_KEYDOWN:
//         {
//             switch (event.key.keysym.scancode)
//             {
//             case SDL_SCANCODE_W:
//             case SDL_SCANCODE_UP:
//                 set_player_velovity_y(player, PLAYER_SPEED);
//                 break;
//             case SDL_SCANCODE_A:
//             case SDL_SCANCODE_LEFT:
//                 set_player_velovity_x(player, -PLAYER_SPEED);
//                 break;
//             case SDL_SCANCODE_S:
//             case SDL_SCANCODE_DOWN:
//                 set_player_velovity_y(player, -PLAYER_SPEED);
//                 break;
//             case SDL_SCANCODE_D:
//             case SDL_SCANCODE_RIGHT:
//                 set_player_velovity_x(player, PLAYER_SPEED);
//                 break;
//             }
//             break;
//         }
//         case SDL_KEYUP:
//         {
//             switch (event.key.keysym.scancode)
//             {
//             case SDL_SCANCODE_W:
//             case SDL_SCANCODE_UP:
//                 set_player_velovity_y(player, 0);
//                 break;
//             case SDL_SCANCODE_A:
//             case SDL_SCANCODE_LEFT:
//                 set_player_velovity_x(player, 0);
//                 break;
//             case SDL_SCANCODE_S:
//             case SDL_SCANCODE_DOWN:
//                 set_player_velovity_y(player, 0);
//                 break;
//             case SDL_SCANCODE_D:
//             case SDL_SCANCODE_RIGHT:
//                 set_player_velovity_x(player, 0);
//                 break;
//             }
//             break;
//         }