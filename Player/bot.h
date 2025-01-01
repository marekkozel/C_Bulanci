#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>
#include <math.h>
#include <assert.h>
#include "Config/sdl.h"
#include "Scenes/Obstacles/obstacles.h"
#include "Config/dynamic_array.h"
#include "Weapons/Power_ups/power_ups.h"
#include "Weapons/Projectils/projectils.h"
#include "Config/sdl.h"
#include "Player/player.h"

void bot_logic(Players *players, Player *player, SDL_Context *window, dynarray *projectils, dynarray *power_ups, Obstacles *obstacles, double time);
