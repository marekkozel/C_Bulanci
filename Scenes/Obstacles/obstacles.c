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
#include "obstacles.h"

void set_obstacles(Obstacles *obstacles, SDL_Context *window)
{
    Obstacle obst;
    init_obstacle(window, obstacles, &obst, 0, "../Assets/Obstacles/rectangle_obstacle.png", 1000, 500);
}

void init_obstacles(Obstacles *obstacles, int size)
{
    obstacles->count_obstacles = size;
    obstacles->obstacles = (Obstacle *)malloc(size * sizeof(Obstacle));
}

void init_obstacle(SDL_Context *window, Obstacles *obstacles, Obstacle *obstacle, int id, char tex[100], int x, int y)
{

    set_obstacle_id(obstacle, id);

    set_obstacle_texture(obstacle, window, tex);

    SDL_Rect *dest = (SDL_Rect *)malloc(sizeof(SDL_Rect));

    SDL_QueryTexture(obstacle->texture, NULL, NULL, &dest->w, &dest->h);
    dest->w *= 5;
    dest->h *= 5;
    dest->x = x;
    dest->y = y;

    set_obstacle_rectangle(obstacle, dest);

    obstacles->obstacles[get_obstacle_id(obstacle)] = *obstacle;
}

// ---------------------------------------

void set_obstacle_id(Obstacle *obstacle, int id)
{
    obstacle->id = id;
}

void set_obstacle_rectangle(Obstacle *obstacle, SDL_Rect *rect)
{
    obstacle->rectangle = rect;
}

void set_obstacle_name(Obstacle *obstacle, char *name)
{
    strcpy(obstacle->name, name);
}

void set_obstacle_texture(Obstacle *obstacle, SDL_Context *window, char *texture)
{
    SDL_Texture *tex = IMG_LoadTexture(window->renderer, texture);
    assert(tex);

    obstacle->texture = tex;
}

int get_obstacle_id(Obstacle *obstacle)
{
    return obstacle->id;
}

int get_obstacle_x(Obstacle *obstacle)
{
    return obstacle->rectangle->x;
}

int get_obstacle_y(Obstacle *obstacle)
{
    return obstacle->rectangle->y;
}

int get_obstacle_w(Obstacle *obstacle)
{
    return obstacle->rectangle->w;
}

int get_obstacle_h(Obstacle *obstacle)
{
    return obstacle->rectangle->h;
}
