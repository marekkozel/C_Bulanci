#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include <assert.h>
#include "Config/sdl.h"

#include "player.h"

void init_players(Players *players)
{

    players->count_players = 0;
    players->players = (Player *)malloc(4 * sizeof(Player) * 2);
}

void add_player(Players *players, Player *player)
{
    // printf("\n%d\n", get_player_id(player));
    players->count_players += 1;
    players->players[get_player_id(player)] = *player;
}

void init_player(Player *player, SDL_Context *window, int id)
{

    set_player_id(player, id);

    SDL_Texture *tex = IMG_LoadTexture(window->renderer, "/home/marek/C_Bulanci/Player/orange_bulanek.png");
    if (!tex)
    {
        printf("error creating texture: %s\n", SDL_GetError());

        SDL_DestroyRenderer(window->renderer);
        SDL_DestroyWindow(window->renderer);
        SDL_Quit();
        return 1;
    }

    set_player_texture(player, tex);
    set_player_health(player, 100);
    set_player_velovity_x(player, 0);
    set_player_velovity_y(player, 0);
    set_player_velovity_x(player, 0);

    SDL_Rect *dest = (SDL_Rect *)malloc(sizeof(SDL_Rect));

    SDL_QueryTexture(player->texture, NULL, NULL, &dest->w, &dest->h);
    dest->w *= 5;
    dest->h *= 5;
    dest->x = 500;
    dest->y = 500;

    set_player_rectangle(player, dest);
}

void move_player(Player *player)
{
    set_player_x(player, get_player_x(player) + get_player_velocity_x(player));
}

void set_player_id(Player *player, int id)
{
    player->id = id;
}

void set_player_rectangle(Player *player, SDL_Rect *rect)
{
    player->rectangle = rect;
}

void set_player_x(Player *player, int x)
{
    player->rectangle->x = x;
}

void set_player_y(Player *player, int y)
{
    player->rectangle->y = y;
}

void set_player_texture(Player *player, SDL_Texture *texture)
{
    player->texture = texture;
}

void set_player_health(Player *player, int health)
{
    player->health = health;
}

void set_player_velovity_x(Player *player, int velocity_x)
{
    player->velocity_x = velocity_x;
}

void set_player_velovity_y(Player *player, int velocity_y)
{
    player->velocity_y = velocity_y;
}

int get_player_id(Player *player)
{
    return player->id;
}

int get_player_velocity_x(Player *player)
{
    return player->velocity_x;
}

int get_player_velocity_y(Player *player)
{
    return player->velocity_y;
}

int get_player_x(Player *player)
{
    return player->rectangle->x;
}

int get_player_y(Player *player)
{
    return player->rectangle->y;
}