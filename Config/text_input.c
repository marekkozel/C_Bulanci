#include "text_input.h"

int text_input(SDL_Context *window, int *close_request, TTF_Font *neco, TTF_Font *main_font)
{

    gameState gs = JVP;
    unsigned int quitter = 0,
                 jvpTexteLength = 0;

    char *jvpTexteInput = (char *)malloc(256 * sizeof(char));
    memset(jvpTexteInput, 0, 256);

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    // Définir la rectangle de la saisie
    SDL_Rect jvpTexteRect;
    jvpTexteRect.x = 248;

    jvpTexteRect.y = 226;
    jvpTexteRect.w = 305;
    jvpTexteRect.h = 98;

    TTF_Font *font = TTF_OpenFont("../Assets/Fonts/Venite.ttf", 64);
    if (font == NULL)
    {
        assert(font);
        printf("Error : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    SDL_Color black = {0, 0, 0};
    SDL_Color white = {255, 255, 255};
    SDL_Surface *jvpSurfaceTexte = NULL;

    SDL_Texture *jvpTexte = NULL;
    SDL_Texture *empty_background = IMG_LoadTexture(window->renderer, "../Assets/background_empty.png");
    SDL_Rect background_rect;
    background_rect.x = 0;
    background_rect.y = 0;
    SDL_QueryTexture(empty_background, NULL, NULL, &background_rect.w, &background_rect.h);

    SDL_Event event;

    while (gs != EXIT)
    {

        SDL_RenderCopy(window->renderer, empty_background, NULL, &background_rect);

        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_BACKSPACE)
            {
                if (gs == JVP && jvpTexteLength > 0)
                {
                    jvpTexteLength--;
                    jvpTexteInput[strlen(jvpTexteInput) - 1] = 0;
                    jvpSurfaceTexte = TTF_RenderText_Solid(main_font, jvpTexteInput, white);
                    jvpTexte = SDL_CreateTextureFromSurface(window->renderer, jvpSurfaceTexte);
                    SDL_QueryTexture(jvpTexte, NULL, NULL, &jvpTexteRect.w, &jvpTexteRect.h);
                }
            }
            break;
        case SDL_TEXTINPUT:
            if (gs == JVP && jvpTexteLength < MAX_NAME_LENGTH)
            {
                jvpTexteLength++;
                strcat(jvpTexteInput, event.text.text);
                jvpSurfaceTexte = TTF_RenderText_Solid(main_font, jvpTexteInput, white);
                jvpTexte = SDL_CreateTextureFromSurface(window->renderer, jvpSurfaceTexte);
                SDL_QueryTexture(jvpTexte, NULL, NULL, &jvpTexteRect.w, &jvpTexteRect.h);
            }
            break;
        }

        SDL_RenderCopy(window->renderer, jvpTexte, NULL, &jvpTexteRect);

        /* À la place de SDL_Flip */
        SDL_RenderPresent(window->renderer);
    }

    SDL_FreeSurface(jvpSurfaceTexte);

    SDL_DestroyTexture(jvpTexte);

    SDL_DestroyRenderer(window->renderer);
    TTF_CloseFont(main_font);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}

void initButtons(Buttons *btns)
{
    // short int w = 305, h = 98;

    // // (x coords)
    // btns->jvjBtn.min_x = btns->jvpBtn.min_x =
    //     btns->retourBtn.min_x = btns->quitterBtn.min_x =
    //         btns->validerBtn.min_x = 248;
    // btns->jvjBtn.max_x = btns->jvpBtn.max_x =
    //     btns->retourBtn.max_x = btns->quitterBtn.max_x =
    //         btns->validerBtn.max_x = 248 + w;
    // // (y coords)
    // btns->jvpBtn.min_y = 206;
    // btns->jvpBtn.max_y = 206 + h;
    // btns->jvjBtn.min_y = btns->validerBtn.min_y = 334;
    // btns->jvjBtn.max_y = btns->validerBtn.max_y = 334 + h;
    // btns->retourBtn.min_y = btns->quitterBtn.min_y = 461;
    // btns->retourBtn.max_y = btns->quitterBtn.max_y = 461 + h;
}
void FreeImages(Images *images)
{
    SDL_DestroyTexture(images->menuTex);
    SDL_DestroyTexture(images->input1Tex);
    SDL_DestroyTexture(images->input2Tex);
}
void chargerImages(Images *images, SDL_Renderer *renderer)
{
    SDL_Surface *s = IMG_Load("../Assets/images/menu.png");
    images->menuTex = SDL_CreateTextureFromSurface(renderer, s);
    s = IMG_Load("../Assets/images/input1.png");
    images->input1Tex = SDL_CreateTextureFromSurface(renderer, s);
    s = IMG_Load("../Assets/images/input2.png");
    images->input2Tex = SDL_CreateTextureFromSurface(renderer, s);
}
