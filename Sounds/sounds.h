#pragma once

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "Config/dynamic_array.h"

#define SDL_OK 0
#define INVALID_AUDIO_DEVICE 0
#define PLAY_AUDIO 0
#define STOP_AUDIO 1

void play_sound();

int initialize_audio();

void audio_callback(void *userData, Uint8 *stream, int length);

void play_audio();

void stop_audio();

void clean_up();
