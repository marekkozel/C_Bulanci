#pragma once

#include <SDL2/SDL.h>

typedef struct
{
    SDL_Window *window;
    SDL_Renderer *renderer;
} SDL_Context;

SDL_Context sdl_context_init(const char *window_name, int width, int height);

SDL_Context sdl_window_setup();

void sdl_context_free(SDL_Context *ctx);