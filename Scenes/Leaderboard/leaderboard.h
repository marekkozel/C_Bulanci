#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <assert.h>
#include "Config/sdl.h"
#include "Player/player.h"

typedef struct
{
    char name[50];
    int score;
} Data;

void write_to_leaderboard(int score, char *user_name);
Data *read_from_leaderboard(int *row_count);

int fsize(FILE *fp);

Data *best_score_sorted(int *row_count);

void bubbleSort(Data *data, int size);
