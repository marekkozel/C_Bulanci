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
#include "sdl.h"
#include "player.h"
#include "Scenes/Obstacles/obstacles.h"
#include "Config/dynamic_array.h"
#include "Weapons/Power_ups/power_ups.h"
#include "Weapons/Projectils/projectils.h"

void init_players(Players *players)
{
    players->count_players = 0;
    players->players = (Player *)malloc(8 * sizeof(Player));
}

void add_player(Players *players, Player *player)
{
    // printf("\n%d\n", get_player_id(player));
    players->count_players += 1;
    players->players[get_player_id(player)] = *player;
}

void init_player(Player *player, SDL_Context *window, int id, char path[100], Color color)
{

    set_player_id(player, id);

    set_player_color(player, color);
    set_player_direction(player, 0, -1);
    set_player_texture(player, window, path);
    set_player_health(player, 100);
    set_player_velovity_x(player, 0);
    set_player_velovity_y(player, 0);
    set_player_velovity_x(player, 0);
    set_player_friction_x(player, 0);
    set_player_friction_y(player, 0);
    set_player_multiplier_x(player, 1);
    set_player_multiplier_y(player, 1);
    set_player_power(player, GUN);

    SDL_Rect *dest = (SDL_Rect *)malloc(sizeof(SDL_Rect));

    SDL_QueryTexture(player->texture, NULL, NULL, &dest->w, &dest->h);
    dest->w *= 5;
    dest->h *= 5;
    dest->x = 500 * id;
    dest->y = 500 * id;

    set_player_rectangle(player, dest);
}

void move_player(Player *player, double delta_time, Players *players, Obstacles *obstacles, dynarray *power_ups, dynarray *projectils)
{
    if (get_player_heath(player) <= 0)
    {
        SDL_Rect rect = {.x = 0, .y = 0, .w = 0, .h = 0};
        set_player_rectangle(player, &rect);
    }

    set_player_multiplier_x(player, 1);
    set_player_multiplier_y(player, 1);

    // Colisions
    detect_players_collisions(player, players);
    detect_boarders_collisions(player);
    detect_obstacles_collisions(player, obstacles);
    detect_power_up_collision(player, power_ups);
    detect_projectils_collision(player, projectils);

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

void animate_player(Player *player, SDL_Context *window, char *path)
{
    set_player_texture(player, window, path);
}

void detect_players_collisions(Player *player, Players *players)
{

    for (int i = 0; i < players->count_players; i++)
    {
        if (get_player_id(player) != players->players[i].id && SDL_HasIntersection(player->rectangle, players->players[i].rectangle))
        {

            if (get_player_y(player) < get_player_y(&players->players[i]) + get_player_h(&players->players[i]) - 10 && get_player_y(player) + get_player_h(player) > get_player_y(&players->players[i]) + 10)
            {

                if (get_player_x(&players->players[i]) <= get_player_x(player) + get_player_w(player) && get_player_x(player) > get_player_x(&players->players[i]) + (get_player_w(&players->players[i]) / 2))
                {
                    if (get_player_velocity_x(player) < 0)
                    {
                        set_player_multiplier_x(player, 0);
                    }
                }
                else if (get_player_x(player) + get_player_w(player) >= get_player_x(&players->players[i]))
                {
                    if (get_player_velocity_x(player) > 0)
                    {
                        set_player_multiplier_x(player, 0);
                    }
                }
            }
            else
            {
                if (get_player_y(&players->players[i]) <= get_player_y(player) + get_player_h(player) && get_player_y(player) > get_player_y(&players->players[i]) + (get_player_h(&players->players[i]) / 2))
                {
                    if (get_player_velocity_y(player) < 0)
                    {
                        set_player_multiplier_y(player, 0);
                    }
                }
                else if (get_player_y(player) + get_player_h(player) >= get_player_y(&players->players[i]))
                {
                    if (get_player_velocity_y(player) > 0)
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

void detect_obstacles_collisions(Player *player, Obstacles *obstacles)
{
    for (int i = 0; i < obstacles->count_obstacles; i++)
    {
        if (SDL_HasIntersection(player->rectangle, obstacles->obstacles[i].rectangle))
        {

            if (get_player_y(player) < get_obstacle_y(&obstacles->obstacles[i]) + get_obstacle_h(&obstacles->obstacles[i]) - 10 && get_player_y(player) + get_player_h(player) > get_obstacle_y(&obstacles->obstacles[i]) + 10)
            {

                if (get_player_x(player) <= get_obstacle_x(&obstacles->obstacles[i]) + get_obstacle_w(&obstacles->obstacles[i]) && get_player_x(player) > get_obstacle_x(&obstacles->obstacles[i]) + (get_obstacle_w(&obstacles->obstacles[i]) / 2))
                {
                    if (player->velocity_x < 0)
                    {
                        set_player_multiplier_x(player, 0);
                    }
                }
                else if (get_player_x(player) + get_player_w(player) >= get_obstacle_x(&obstacles->obstacles[i]))
                {
                    if (player->velocity_x > 0)
                    {
                        set_player_multiplier_x(player, 0);
                    }
                }
            }
            else
            {
                if (get_player_y(player) <= get_obstacle_y(&obstacles->obstacles[i]) + get_obstacle_h(&obstacles->obstacles[i]) && get_player_y(player) > get_obstacle_y(&obstacles->obstacles[i]) + (get_obstacle_h(&obstacles->obstacles[i]) / 2))
                {
                    if (player->velocity_y < 0)
                    {
                        set_player_multiplier_y(player, 0);
                    }
                }
                else if (get_player_y(player) + get_player_h(player) >= get_obstacle_y(&obstacles->obstacles[i]))
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

void detect_power_up_collision(Player *player, dynarray *array)
{
    for (int i = 0; i < array->size; i++)
    {
        Power_up *power_up;
        power_up = dynarray_get(array, i);

        if (SDL_HasIntersection(player->rectangle, power_up->rectangle))
        {
            set_player_power(player, get_power_up_power(power_up));
            dynarray_remove(array, power_up);
        }
    }
}

void detect_projectils_collision(Player *player, dynarray *projectils)
{
    for (int i = 0; i < projectils->size; i++)
    {
        Projectil *projectil;
        projectil = dynarray_get(projectils, i);

        if (SDL_HasIntersection(player->rectangle, projectil->rectangle) && get_projectil_player_id(projectil) != get_player_id(player))
        {
            player->health -= 50;
            printf("damaged, player_id: %d", get_player_id(player));
            dynarray_remove(projectils, projectil);
        }
    }
}

void spawn_projectil(Player *player, dynarray *projectils, SDL_Context *window)
{
    char path[100] = "";
    switch (get_player_power(player))
    {
    case GUN:
        strcpy(path, "../Assets/Projectils/bullet.png");
        break;

    default:
        break;
    }

    init_projectil(projectils, window, 0, get_player_id(player), get_player_x(player) + (get_player_w(player) / 2), get_player_y(player) + (get_player_h(player) / 2), get_player_direction_x(player), get_player_direction_y(player), path);
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

void set_player_texture(Player *player, SDL_Context *window, char *path)
{
    char color[100] = "";
    char direction[100] = "";
    char image_path[500] = "";
    switch (get_player_color(player))
    {
    case RED:
        strcpy(color, "red");
        break;

    case BLUE:
        strcpy(color, "blue");
        break;

    case GREEN:
        strcpy(color, "green");
        break;

    case ORANGE:
        strcpy(color, "orange");
        break;

    default:
        strcpy(color, "orange");
        break;
    }

    if (get_player_direction_x(player) > 0)
    {
        strcpy(direction, "right");
    }
    else if (get_player_direction_x(player) < 0)
    {
        strcpy(direction, "left");
    }

    if (get_player_direction_y(player) > 0)
    {
        strcpy(direction, "down");
    }
    else if (get_player_direction_y(player) < 0)
    {
        strcpy(direction, "up");
    }

    sprintf(image_path, "%s%s_bulanek_%s.png", path, color, direction);

    SDL_Texture *tex = IMG_LoadTexture(window->renderer, image_path);
    assert(tex);

    player->texture = tex;
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

void set_player_direction(Player *player, int direction_x, int direction_y)
{
    player->direction_x = direction_x;
    player->direction_y = direction_y;
}

void set_player_color(Player *player, Color color)
{
    player->color = color;
}

void set_player_power(Player *player, Power power)
{
    player->power = power;
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

int get_player_direction_x(Player *player)
{
    return player->direction_x;
}

int get_player_direction_y(Player *player)
{
    return player->direction_y;
}

int get_player_heath(Player *player)
{
    return player->health;
}

Color get_player_color(Player *player)
{
    return player->color;
}

Power get_player_power(Player *player)
{
    return player->power;
}
