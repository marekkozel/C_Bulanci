#pragma once

#include <SDL2/SDL.h>
#include "Config/sdl.h"

#define PLAYER_SPEED (100)

typedef struct
{
    int id;

    SDL_Rect *rectangle;
    int velocity_x;
    int velocity_y;
    SDL_Texture *texture;

    int health;

} Player;

typedef struct
{
    int count_players;
    Player *players;
} Players;

void init_players(Players *players);
void add_player(Players *players, Player *player);

void init_player(Player *player, SDL_Context *window, int id);

void move_player(Player *player);

void set_player_id(Player *player, int id);
void set_player_rectangle(Player *player, SDL_Rect *rect);
void set_player_x(Player *player, int x);
void set_player_y(Player *player, int y);
void set_player_texture(Player *player, SDL_Texture *texture);
void set_player_health(Player *player, int health);
void set_player_velovity_x(Player *player, int velocity_x);
void set_player_velovity_y(Player *player, int velocity_y);

int get_player_id(Player *player);
int get_player_velocity_x(Player *player);
int get_player_velocity_y(Player *player);
int get_player_x(Player *player);
int get_player_y(Player *player);
