#pragma once

#include "Config/dynamic_array.h"
#include <SDL2/SDL.h>
#include "Config/sdl.h"
#include "Scenes/Obstacles/obstacles.h"

#define PROJECTIL_SPEED (1000)

typedef struct
{
    int id;
    int player_id;
    SDL_Rect *rectangle;
    double velocity_x;
    double velocity_y;

    int direction_x;
    int direction_y;

    SDL_Texture *texture;

} Projectil;

void init_projectils(dynarray *power_ups);

void init_projectil(dynarray *projectils, SDL_Context *window, int id, int player_id, int x, int y, int direction_x, int direction_y, char *path);

void move_projectil(Projectil *projectil, double delta_time);

void set_projectil_id(Projectil *projectil, int id);

void set_projectil_player_id(Projectil *projectil, int player_id);

void set_projectil_rectangle(Projectil *projectil, SDL_Rect *rect);

void set_projectil_x(Projectil *projectil, double x);

void set_projectil_y(Projectil *projectil, double y);

void set_projectil_power(Projectil *projectil, Power power);

void set_projectil_texture(Projectil *projectil, SDL_Context *window, char *texture);

void set_projectil_direction(Projectil *projectil, int direction_x, int direction_y);

void set_projectil_velocity_x(Projectil *projectil, double velocity_x);

void set_projectil_velocity_y(Projectil *projectil, double velocity_y);

int get_projectil_id(Projectil *projectil);

int get_projectil_player_id(Projectil *projectil);

int get_projectil_x(Projectil *projectil);

int get_projectil_y(Projectil *projectil);

int get_projectil_w(Projectil *projectil);

int get_projectil_h(Projectil *projectil);

double get_projectil_velocity_x(Projectil *projectil);

double get_projectil_velocity_y(Projectil *projectil);

int get_projectil_direction_x(Projectil *projectil);

int get_projectil_direction_y(Projectil *projectil);
