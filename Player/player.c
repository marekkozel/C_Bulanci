#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include <math.h>
#include <assert.h>
#include "Config/sdl.h"

#include "player.h"

void init_players(Players *players)
{
    players->count_players = 0;
    players->players = (Player *)malloc(4 * sizeof(Player));
}

void add_player(Players *players, Player *player)
{
    // printf("\n%d\n", get_player_id(player));
    players->count_players += 1;
    players->players[get_player_id(player)] = *player;
}

void init_player(Player *player, SDL_Context *window, int id, SDL_Texture *tex)
{

    set_player_id(player, id);

    set_player_texture(player, tex);
    set_player_health(player, 100);
    set_player_velovity_x(player, 0);
    set_player_velovity_y(player, 0);
    set_player_velovity_x(player, 0);
    set_player_friction_x(player, 0);
    set_player_friction_y(player, 0);
    set_player_multiplier_x(player, 1);
    set_player_multiplier_y(player, 1);

    SDL_Rect *dest = (SDL_Rect *)malloc(sizeof(SDL_Rect));

    SDL_QueryTexture(player->texture, NULL, NULL, &dest->w, &dest->h);
    dest->w *= 5;
    dest->h *= 5;
    dest->x = 500 * id;
    dest->y = 500 * id;

    set_player_rectangle(player, dest);
}

void move_player(Player *player, double delta_time, Players *players)
{
    set_player_multiplier_x(player, 1);
    set_player_multiplier_y(player, 1);

    // Colisions
    detect_players_collisions(player, players);
    detect_boarders_collisions(player);

    // Movement
    double velocity_x = get_player_velocity_x(player);
    double velocity_y = get_player_velocity_y(player);

    set_player_x(player, (double)get_player_x(player) + (velocity_x * delta_time) * get_player_multiplier_x(player));
    set_player_y(player, (double)get_player_y(player) + (velocity_y * delta_time) * get_player_multiplier_y(player));

    if (velocity_x > -55 && velocity_x < 55)
    {
        velocity_x = 0;
    }
    else if (velocity_x > 0)
    {
        velocity_x -= player->friction_x;
    }
    else if (velocity_x < 0)
    {
        velocity_x += player->friction_x;
    }

    if (velocity_y > -55 && velocity_y < 55)
    {
        velocity_y = 0;
    }
    else if (velocity_y > 0)
    {
        velocity_y -= player->friction_y;
    }
    else if (velocity_y < 0)
    {
        velocity_y += player->friction_y;
    }
    set_player_velovity_x(player, velocity_x);
    set_player_velovity_y(player, velocity_y);
}

void detect_players_collisions(Player *player, Players *players)
{

    for (int i = 0; i < players->count_players; i++)
    {
        if (player->id != players->players[i].id && SDL_HasIntersection(player->rectangle, players->players[i].rectangle))
        {

            if (get_player_y(player) < get_player_y(&players->players[i]) + get_player_h(&players->players[i]) - 10 && get_player_y(player) + get_player_h(player) > get_player_y(&players->players[i]) + 10)
            {

                if (get_player_x(player) <= players->players[i].rectangle->x + players->players[i].rectangle->w && get_player_x(player) > players->players[i].rectangle->x + (players->players[i].rectangle->w / 2))
                {
                    if (player->velocity_x < 0)
                    {
                        set_player_multiplier_x(player, 0);
                    }
                }
                else if (get_player_x(player) + get_player_w(player) >= players->players[i].rectangle->x)
                {
                    if (player->velocity_x > 0)
                    {
                        set_player_multiplier_x(player, 0);
                    }
                }
            }
            else
            {
                if (get_player_y(player) <= players->players[i].rectangle->y + players->players[i].rectangle->h && get_player_y(player) > players->players[i].rectangle->y + (players->players[i].rectangle->h / 2))
                {
                    if (player->velocity_y < 0)
                    {
                        set_player_multiplier_y(player, 0);
                    }
                }
                else if (get_player_y(player) + get_player_h(player) >= players->players[i].rectangle->y)
                {
                    if (player->velocity_y > 0)
                    {
                        set_player_multiplier_y(player, 0);
                    }
                }
            }
        }
    }
}

void detect_boarders_collisions(Player *player)
{
    if (get_player_x(player) <= 0)
        set_player_x(player, 0);
    if (get_player_y(player) <= 0)
        set_player_y(player, 0);

    if (get_player_x(player) >= WINDOW_WIDTH - get_player_w(player))
        set_player_x(player, WINDOW_WIDTH - get_player_w(player));
    if (get_player_y(player) >= WINDOW_HEIGHT - get_player_h(player))
        set_player_y(player, WINDOW_HEIGHT - get_player_h(player));
}

// ______________________________________________________________________

void set_player_friction_x(Player *player, int friction)
{
    player->friction_x = friction;
}

void set_player_friction_y(Player *player, int friction)
{
    player->friction_y = friction;
}

void set_player_id(Player *player, int id)
{
    player->id = id;
}

void set_player_rectangle(Player *player, SDL_Rect *rect)
{
    player->rectangle = rect;
}

void set_player_x(Player *player, double x)
{
    player->rectangle->x = floor(x);
}

void set_player_y(Player *player, double y)
{
    player->rectangle->y = floor(y);
}

void set_player_w(Player *player, int w)
{
    player->rectangle->w = w;
}

void set_player_h(Player *player, int h)
{
    player->rectangle->h = h;
}

void set_player_texture(Player *player, SDL_Texture *texture)
{
    player->texture = texture;
}

void set_player_health(Player *player, int health)
{
    player->health = health;
}

void set_player_velovity_x(Player *player, double velocity_x)
{

    player->velocity_x = velocity_x;
}

void set_player_velovity_y(Player *player, double velocity_y)
{
    player->velocity_y = velocity_y;
}

void set_player_multiplier_x(Player *player, int multiplier)
{
    player->multiplier_x = multiplier;
}

void set_player_multiplier_y(Player *player, int multiplier)
{
    player->multiplier_y = multiplier;
}

int get_player_id(Player *player)
{
    return player->id;
}

double get_player_velocity_x(Player *player)
{
    return player->velocity_x;
}

double get_player_velocity_y(Player *player)
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

int get_player_w(Player *player)
{
    return player->rectangle->w;
}

int get_player_h(Player *player)
{
    return player->rectangle->h;
}

int get_player_multiplier_x(Player *player)
{
    return player->multiplier_x;
}

int get_player_multiplier_y(Player *player)
{
    return player->multiplier_y;
}