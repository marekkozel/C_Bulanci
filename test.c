#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>

int main(int argc, char *argv[])
{
    // Inicializace SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Vytvoření okna
    SDL_Window *window = SDL_CreateWindow(
        "SDL experiments", // Titulek okna
        100,               // Souřadnice x
        100,               // Souřadnice y
        800,               // Šířka
        600,               // Výška
        SDL_WINDOW_SHOWN   // Okno se má po vytvoření rovnou zobrazit
    );
    // Vytvoření kreslítka
    SDL_Renderer *renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_Event event;
    int running = 1;
    int line_x = 100;

    while (running == 1)
    {
        // Dokud jsou k dispozici nějaké události, ukládej je do proměnné `event`
        while (SDL_PollEvent(&event))
        {
            // Pokud došlo k uzavření okna, nastav proměnnou `running` na `0`
            if (event.type == SDL_QUIT)
            {
                running = 0;
            }
        }

        // Posuň pozici čáry doprava
        line_x++;

        // Nastav barvu vykreslování na černou
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        // Vykresli pozadí
        SDL_RenderClear(renderer);

        // Nastav barvu vykreslování na červenou
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

        // Vykresli čáru
        SDL_RenderDrawLine(renderer, line_x, 50, line_x, 250);

        // Zobraz vykreslené prvky na obrazovku
        SDL_RenderPresent(renderer);
    }

    // Uvolnění prostředků
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}