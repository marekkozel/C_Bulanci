#pragma once

#include "Config/dynamic_array.h"
#include <SDL2/SDL.h>
#include "Config/sdl.h"
#include "Scenes/Obstacles/obstacles.h"

typedef enum
{
    GUN,
    SHOTGUN,
    ROCKET,
    MINE
} Power;

typedef struct
{
    int id;
    SDL_Rect *rectangle;
    Power power;
    SDL_Texture *texture;
} Power_up;

void init_power_ups(dynarray *power_ups);

void init_power_up(dynarray *power_ups, SDL_Context *window, int id, int x, int y, Power power, char *path);

void spawn_power_up(dynarray *power_ups, SDL_Context *window, int timer);

void power_up_collision(Power_up *power_up, dynarray *power_ups);

void set_power_up_id(Power_up *power_up, int id);

void set_power_up_rectangle(Power_up *power_up, SDL_Rect *rect);

void set_power_up_x(Power_up *power_up, double x);

void set_power_up_y(Power_up *power_up, double y);

void set_power_up_power(Power_up *power_up, Power power);

void set_power_up_texture(Power_up *power_up, SDL_Context *window, char *texture);

int get_power_up_id(Power_up *power_up);

int get_power_up_x(Power_up *power_up);

int get_power_up_w(Power_up *power_up);

int get_power_up_h(Power_up *power_up);

Power get_power_up_power(Power_up *power_up);
