#pragma once

#include <SDL2/SDL.h>
#include "sdl.h"
#include "Player/player.h"
#include "Weapons/Projectils/projectils.h"

void read_keys(int *close_request, SDL_Context *window, Players *players, dynarray *projectils, double timer);
