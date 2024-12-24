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

typedef struct
{
    SDL_Color color;
    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Rect rect;
    TTF_Font *font;
    bool is_text_big;

} Text;

typedef enum
{
    ROBOT,
    PLAYER,
    NOTHING
} Icon_type;

typedef struct
{
    int id;
    Icon_type type;
    SDL_Rect rect;
    SDL_Texture *texture;
    SDL_Rect player_icon_rect;
    SDL_Texture *player_icon_texture;
    Color color;
    Text player_arrow_left;
    Text player_arrow_right;
    Text icon_arrow_left;
    Text icon_arrow_right;

} Icon;

void init_Text(Text *text, SDL_Color color, TTF_Font *font, char input_text[100], SDL_Context *window);

void init_Icon(Icon *icon, int id, Color color, SDL_Context *window, TTF_Font *font);

void start_main_menu(Players *palyers, SDL_Context *window, int *close_request, TTF_Font *font, TTF_Font *main_font);

void new_game(Players *players, TTF_Font *font, TTF_Font *main_font, SDL_Context *window, int *close_request);

void mouse_hover(int xMouse, int yMouse, Text *text);

bool is_mouse_hover(int xMouse, int yMouse, SDL_Rect *rect);

void set_menu_texture_big(SDL_Rect *rect, SDL_Texture *texture);

void set_menu_texture_small(SDL_Rect *rect, SDL_Texture *texture);

void set_text_rectangle(Text *text, SDL_Rect *rect);

void set_text_x(Text *text, double x);

void set_text_y(Text *text, double y);

void set_text_w(Text *text, int w);

void set_text_h(Text *text, int h);

void set_text_surface(Text *text, SDL_Surface *surface);

void set_text_texture(Text *text, SDL_Texture *texture);

void set_text_font(Text *text, TTF_Font *font);

void set_text_color(Text *text, SDL_Color color);

void set_text_is_big(Text *text, bool is_big);

void set_icon_id(Icon *icon, int id);

void set_icon_rectangle(Icon *icon, SDL_Rect *rect);

void set_icon_player_rectangle(Icon *icon, SDL_Rect *rect);

void set_icon_x(Icon *icon, double x);

void set_icon_y(Icon *icon, double y);

void set_icon_w(Icon *icon, int w);

void set_icon_h(Icon *icon, int h);

void set_icon_texture(Icon *icon, SDL_Context *window);

void set_icon_player_texture(Icon *icon, SDL_Context *window);

void set_icon_player_arrow_left(Icon *icon, Text text);

void set_icon_player_arrow_right(Icon *icon, Text text);

void set_icon_icon_arrow_left(Icon *icon, Text text);

void set_icon_icon_arrow_right(Icon *icon, Text text);

void set_icon_color(Icon *icon, Color color);

void set_icon_type(Icon *icon, Icon_type type);

int get_text_x(Text *text);

int get_text_y(Text *text);

int get_text_w(Text *text);

int get_text_h(Text *text);

SDL_Color get_text_color(Text *text);

SDL_Surface *get_text_surface(Text *text);

SDL_Texture *get_text_texture(Text *text);

SDL_Rect *get_text_rectangle(Text *text);

TTF_Font *get_text_font(Text *text);

bool get_text_is_big(Text *text);

int get_icon_x(Icon *icon);

int get_icon_y(Icon *icon);

int get_icon_w(Icon *icon);

int get_icon_h(Icon *icon);

Color get_icon_color(Icon *icon);

SDL_Texture *get_icon_texture(Icon *icon);

SDL_Rect *get_icon_rectangle(Icon *icon);

SDL_Texture *get_icon_player_texture(Icon *icon);

SDL_Rect *get_icon_player_rectangle(Icon *icon);

Icon_type get_icon_type(Icon *icon);

Text *get_icon_player_arrow_left(Icon *icon);

Text *get_icon_player_arrow_right(Icon *icon);

Text *get_icon_icon_arrow_left(Icon *icon);

Text *get_icon_icon_arrow_right(Icon *icon);
