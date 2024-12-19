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
#include "power_ups.h"
#include "Config/dynamic_array.h"

void init_power_ups(dynarray *power_ups)
{
    dynarray_init(power_ups, 1);
}

void init_power_up(dynarray *power_ups, SDL_Context *window, int id, int x, int y, Power power, char *path)
{
    Power_up *power_up = (Power_up *)malloc(sizeof(Power_up));
    set_power_up_id(power_up, id);
    set_power_up_texture(power_up, window, path);
    set_power_up_power(power_up, power);

    SDL_Rect *dest = (SDL_Rect *)malloc(sizeof(SDL_Rect));

    SDL_QueryTexture(power_up->texture, NULL, NULL, &dest->w, &dest->h);
    dest->w *= 5;
    dest->h *= 5;
    dest->x = x;
    dest->y = y;

    set_power_up_rectangle(power_up, dest);

    dynarray_push(power_ups, power_up);
}

void spawn_power_up(dynarray *power_ups, SDL_Context *window, int timer)
{
    if (timer % 10 == 0)
    {
        char path[500] = "../Assets/Power_ups/power_up.png";
        init_power_up(power_ups, window, 0, rand() % 1920, rand() % 1080, SHOTGUN, path);
    }
}

//-----------------------------------
// Setters

void set_power_up_id(Power_up *power_up, int id)
{
    power_up->id = id;
}

void set_power_up_rectangle(Power_up *power_up, SDL_Rect *rect)
{
    power_up->rectangle = rect;
}

void set_power_up_x(Power_up *power_up, double x)
{
    power_up->rectangle->x = floor(x);
}

void set_power_up_y(Power_up *power_up, double y)
{
    power_up->rectangle->y = floor(y);
}

void set_power_up_power(Power_up *power_up, Power power)
{
    power_up->power = power;
}

void set_power_up_texture(Power_up *power_up, SDL_Context *window, char *texture)
{
    SDL_Texture *tex = IMG_LoadTexture(window->renderer, texture);
    assert(tex);

    power_up->texture = tex;
}

// Geters

int get_power_up_id(Power_up *power_up)
{
    return power_up->id;
}

int get_power_up_x(Power_up *power_up)
{
    return power_up->rectangle->x;
}

int get_power_up_y(Power_up *power_up)
{
    return power_up->rectangle->y;
}

int get_power_up_w(Power_up *power_up)
{
    return power_up->rectangle->w;
}

int get_power_up_h(Power_up *power_up)
{
    return power_up->rectangle->h;
}

Power get_power_up_power(Power_up *power_up)
{
    return power_up->power;
}
