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

void write_to_leaderboard(Player *player, char *user_name);

void read_from_leaderboard();
