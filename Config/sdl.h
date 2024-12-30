#pragma once

#include <SDL2/SDL.h>

#define WINDOW_WIDTH (1920)
#define WINDOW_HEIGHT (1080)

typedef struct
{
    SDL_Window *window;
    SDL_Renderer *renderer;
} SDL_Context;

SDL_Context sdl_context_init(const char *window_name, int width, int height);

SDL_Context sdl_window_setup();
