#pragma once

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

typedef struct
{
    int id;
    SDL_Rect *rectangle;
    char name[100];
    SDL_Texture *texture;
} Obstacle;

typedef struct
{
    int count_obstacles;
    int capacity;
    Obstacle *obstacles;
} Obstacles;

void set_obstacles(Obstacles *obstacles, SDL_Context *window);

void init_obstacles(Obstacles *obstacles, int size);

void init_obstacle(SDL_Context *window, Obstacles *obstacles, int id, char *tex, int x, int y);

void set_obstacle_id(Obstacle *obstacle, int id);

void set_obstacle_rectangle(Obstacle *obstacle, SDL_Rect *rect);

void set_obstacle_name(Obstacle *obstacle, char *name);

void set_obstacle_texture(Obstacle *obstacle, SDL_Context *window, char *texture);

int get_obstacle_id(Obstacle *obstacle);

int get_obstacle_x(Obstacle *obstacle);

int get_obstacle_y(Obstacle *obstacle);

int get_obstacle_w(Obstacle *obstacle);

int get_obstacle_h(Obstacle *obstacle);
