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
#include "sdl.h"
#include "player.h"
#include "Scenes/Leaderboard/leaderboard.h"

#define MAX_NAME_LENGTH 16

typedef enum gameState
{
    MENU,
    JVJ,
    JVP,
    EXIT
} gameState;

typedef struct Images
{
    SDL_Texture *menuTex;
    SDL_Texture *input1Tex;
    SDL_Texture *input2Tex;

} Images;

typedef struct Button
{
    int min_x, max_x, min_y, max_y;
} Button;

typedef struct Buttons
{
    Button jvjBtn;
    Button jvpBtn;
    Button quitterBtn;
    Button validerBtn;
    Button retourBtn;
} Buttons;

typedef enum BOOL
{
    TRUE = 1,
    FALSE = 0
} BOOL;

void FreeImages(Images *images);
void chargerImages(Images *images, SDL_Renderer *renderer);
int text_input();
int text_input(SDL_Context *window, int *close_request, TTF_Font *font, TTF_Font *main_font);
void initButtons(Buttons *btns);
