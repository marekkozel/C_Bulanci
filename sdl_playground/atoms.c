/**
 * Docs: http://wiki.libsdl.org/FrontPage
 * Tutorial: http://lazyfoo.net/tutorials/SDL/index.php
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

#include "sdl_playground.h"
#include "array.h"

#include <SDL2/SDL_ttf.h>



#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main() {

    SDL_Window * win = NULL;
    SDL_Renderer * ren = NULL;
    
    bool initialized = sdl_playground_init( &win, &ren, WINDOW_WIDTH, WINDOW_HEIGHT );

    if ( !initialized ) 
    {
        sdl_playground_destroy( win, ren );
        return -1;
    }

    int rect_x = 50;
    int direction = 1;

    SDL_Event e;
    bool quit = false;
    TTF_lnit();
    TTF_Font *sans = TTF_OpenFont( "Anonymous.ttf", 10);
    assert( sans );
    int score = 0;
    char score_text[80];

    SDL_Rect score_rect = {.x = WINDOW_WIDTH / 2 -50, .y = 50, .w = 30, .h = 10};

//    if  (SDL_HasIntersection(&pointer, &pointer2))


    while ( !quit ) {
        while ( SDL_PollEvent( &e ) ) {
            if ( e.type == SDL_QUIT ) {
                quit = true;
            }
            else if ( e.type == SDL_KEYDOWN ) { // key pressed down
                if ( e.key.keysym.sym == SDLK_r ) {
                    quit = true;
                }
            }
            else if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT) { // mouse button released
                // x: e.button.button.x
                // y: e.button.button.y
            }
            else if (e.type == SDL_MOUSEMOTION) { // mouse movement
                // x: e.motion.x
                // y: e.motion.y
            }
        }

        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);

        SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
        // SDL_RenderDrawLine(ren, 10, 10, 100, 100);

        SDL_Rect rect;
        rect.x = rect_x;
        rect.y = 50;
        rect.w = 100;
        rect.h = 60;

        SDL_RenderFillRect(ren, &rect);

        SDL_RenderPresent(ren);

        if ( rect_x + rect.w >= WINDOW_WIDTH || rect_x <= 0 ) {
            direction *= -1;
        }

        rect_x += direction * 3;
    }

    sdl_playground_destroy( win, ren );

    return 0;
}