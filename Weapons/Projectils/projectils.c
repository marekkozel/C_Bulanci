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
#include "Player/player.h"
#include "Scenes/Obstacles/obstacles.h"
#include "Config/dynamic_array.h"
#include "Weapons/Power_ups/power_ups.h"
#include "projectils.h"

void init_projectils(dynarray *projectils)
{
    dynarray_init(projectils, 1);
}

void init_projectil(dynarray *projectils, SDL_Context *window, int id, int player_id, int x, int y, int direction_x, int direction_y, char *path)
{
    Projectil *projectil = (Projectil *)malloc(sizeof(Projectil));

    set_projectil_id(projectil, id);
    set_projectil_player_id(projectil, player_id);
    set_projectil_velocity_x(projectil, PROJECTIL_SPEED * direction_x);
    set_projectil_velocity_y(projectil, PROJECTIL_SPEED * direction_y);

    set_projectil_texture(projectil, window, path);

    SDL_Rect *dest = (SDL_Rect *)malloc(sizeof(SDL_Rect));

    SDL_QueryTexture(projectil->texture, NULL, NULL, &dest->w, &dest->h);
    dest->w *= 5;
    dest->h *= 5;
    dest->x = x - dest->w / 2;
    dest->y = y - dest->h / 2 - 5;

    set_projectil_rectangle(projectil, dest);

    dynarray_push(projectils, projectil);
}

void move_projectil(Projectil *projectil, double delta_time)
{
    double velocity_x = get_projectil_velocity_x(projectil);
    double velocity_y = get_projectil_velocity_y(projectil);

    set_projectil_x(projectil, (double)get_projectil_x(projectil) + (velocity_x * delta_time));
    set_projectil_y(projectil, (double)get_projectil_y(projectil) + (velocity_y * delta_time));
}

//------------

void set_projectil_id(Projectil *projectil, int id)
{
    projectil->id = id;
}

void set_projectil_player_id(Projectil *projectil, int player_id)
{
    projectil->player_id = player_id;
}

void set_projectil_rectangle(Projectil *projectil, SDL_Rect *rect)
{
    projectil->rectangle = rect;
}

void set_projectil_x(Projectil *projectil, double x)
{
    projectil->rectangle->x = floor(x);
}

void set_projectil_y(Projectil *projectil, double y)
{
    projectil->rectangle->y = floor(y);
}

void set_projectil_velocity_x(Projectil *projectil, double velocity_x)
{
    projectil->velocity_x = velocity_x;
}
void set_projectil_velocity_y(Projectil *projectil, double velocity_y)
{
    projectil->velocity_y = velocity_y;
}

void set_projectil_texture(Projectil *projectil, SDL_Context *window, char *texture)
{
    SDL_Texture *tex = IMG_LoadTexture(window->renderer, texture);
    assert(tex);

    projectil->texture = tex;
}

void set_projectil_direction(Projectil *projectil, int direction_x, int direction_y)
{
    projectil->direction_x = direction_x;
    projectil->direction_y = direction_y;
}

// Geters

int get_projectil_id(Projectil *projectil)
{
    return projectil->id;
}

int get_projectil_player_id(Projectil *projectil)
{
    return projectil->player_id;
}

int get_projectil_x(Projectil *projectil)
{
    return projectil->rectangle->x;
}

int get_projectil_y(Projectil *projectil)
{
    return projectil->rectangle->y;
}

int get_projectil_w(Projectil *projectil)
{
    return projectil->rectangle->w;
}

int get_projectil_h(Projectil *projectil)
{
    return projectil->rectangle->h;
}

double get_projectil_velocity_x(Projectil *projectil)
{
    return projectil->velocity_x;
}
double get_projectil_velocity_y(Projectil *projectil)
{
    return projectil->velocity_y;
}

int get_projectil_direction_x(Projectil *projectil)
{
    return projectil->direction_x;
}

int get_projectil_direction_y(Projectil *projectil)
{
    return projectil->direction_y;
}
