// Let's assume that your method of input is a mouse
// since this is long, you can create a class for this then recall it in the gameloop

#include "main_menu.h"

void init_Text(Text *text, SDL_Color color, TTF_Font *font, char input_text[100], SDL_Context *window)
{
    // Main text
    set_text_surface(text, TTF_RenderText_Solid(font, input_text, color));
    set_text_texture(text, SDL_CreateTextureFromSurface(window->renderer, get_text_surface(text)));

    // The game button's rect
    SDL_Rect *rect = (SDL_Rect *)malloc(sizeof(SDL_Rect));
    SDL_QueryTexture(get_text_texture(text), NULL, NULL, &rect->w, &rect->h);

    set_text_color(text, color);
    set_text_font(text, font);
    set_text_rectangle(text, rect);
    set_text_is_big(text, false);
}

void init_Icon(Icon *icon, int id, Color color, SDL_Context *window, TTF_Font *font)
{
    int x_offset = 3;
    int y_offset = 10;
    SDL_Color RGB_WHITE = {255, 255, 255};

    // Main icon
    set_icon_id(icon, id);
    set_icon_type(icon, NOTHING);
    set_icon_texture(icon, window);

    // The game button's rect
    SDL_Rect *rect = (SDL_Rect *)malloc(sizeof(SDL_Rect));
    SDL_QueryTexture(get_icon_texture(icon), NULL, NULL, &rect->w, &rect->h);
    rect->w *= 5;
    rect->h *= 5;
    rect->x = (WINDOW_WIDTH / x_offset) * 2 - rect->w / 2;
    rect->y = (WINDOW_HEIGHT / y_offset) * 2 * (id + 1) - 15;
    set_icon_rectangle(icon, rect);

    set_icon_color(icon, color);

    rect->x = WINDOW_WIDTH / x_offset - rect->w / 2;
    set_icon_player_rectangle(icon, rect);
    set_icon_player_texture(icon, window);

    char arrow_left[100] = "<";
    char arrow_right[100] = ">";

    // player_arrow_left
    Text player_arrow_left;
    init_Text(&player_arrow_left, RGB_WHITE, font, arrow_left, window);
    set_text_x(&player_arrow_left, WINDOW_WIDTH / x_offset - get_text_w(&player_arrow_left) / 2 - get_icon_w(icon) - 50);
    set_text_y(&player_arrow_left, (WINDOW_HEIGHT / y_offset) * 2 * (id + 1));
    set_icon_player_arrow_left(icon, player_arrow_left);

    // player_arrow_right
    Text player_arrow_right;
    init_Text(&player_arrow_right, RGB_WHITE, font, arrow_right, window);
    set_text_x(&player_arrow_right, WINDOW_WIDTH / x_offset - get_text_w(&player_arrow_right) / 2 + get_icon_w(icon) + 50);
    set_text_y(&player_arrow_right, (WINDOW_HEIGHT / y_offset) * 2 * (id + 1));
    set_icon_player_arrow_right(icon, player_arrow_right);

    // icon_arrow_left
    Text icon_arrow_left;
    init_Text(&icon_arrow_left, RGB_WHITE, font, arrow_left, window);
    set_text_x(&icon_arrow_left, (WINDOW_WIDTH / x_offset) * 2 - get_text_w(&icon_arrow_left) / 2 - get_icon_w(icon) - 50);
    set_text_y(&icon_arrow_left, (WINDOW_HEIGHT / y_offset) * 2 * (id + 1));
    set_icon_icon_arrow_left(icon, icon_arrow_left);

    // icon_arrow_right
    Text icon_arrow_right;
    init_Text(&icon_arrow_right, RGB_WHITE, font, arrow_right, window);
    set_text_x(&icon_arrow_right, (WINDOW_WIDTH / x_offset) * 2 - get_text_w(&icon_arrow_right) / 2 + get_icon_w(icon) + 50);
    set_text_y(&icon_arrow_right, (WINDOW_HEIGHT / y_offset) * 2 * (id + 1));
    set_icon_icon_arrow_right(icon, icon_arrow_right);
}

void start_main_menu(Players *players, SDL_Context *window, int *close_request, TTF_Font *font, TTF_Font *main_font)
{

    bool play1 = false;
    bool is_new_game = false;

    SDL_Texture *background = IMG_LoadTexture(window->renderer, "../Assets/background_empty.png");

    SDL_Rect background_rect;
    background_rect.x = 0;
    background_rect.y = 0;
    SDL_QueryTexture(background, NULL, NULL, &background_rect.w, &background_rect.h);

    char main_text[100] = "CUBES BATTLE";
    char newGame_text[100] = "New Game";
    char leaderboard_text[100] = "Leaderboard";
    char exitGame_text[100] = "Exit Game";

    SDL_Color RGB_WHITE = {255, 255, 255};

    Text main_Text;
    init_Text(&main_Text, RGB_WHITE, main_font, main_text, window);
    set_text_x(&main_Text, WINDOW_WIDTH / 2 - get_text_w(&main_Text) / 2);
    set_text_y(&main_Text, (WINDOW_HEIGHT / 9));

    // New Game
    Text newGame_Text;
    init_Text(&newGame_Text, RGB_WHITE, font, newGame_text, window);
    set_text_x(&newGame_Text, WINDOW_WIDTH / 2 - get_text_w(&newGame_Text) / 2);
    set_text_y(&newGame_Text, (WINDOW_HEIGHT / 9) * 3);

    // Leadboard
    Text leaderboard_Text;
    init_Text(&leaderboard_Text, RGB_WHITE, font, leaderboard_text, window);
    set_text_x(&leaderboard_Text, WINDOW_WIDTH / 2 - get_text_w(&leaderboard_Text) / 2);
    set_text_y(&leaderboard_Text, (WINDOW_HEIGHT / 9) * 4);

    // Exit Game
    Text exitGame_Text;
    init_Text(&exitGame_Text, RGB_WHITE, font, exitGame_text, window);
    set_text_x(&exitGame_Text, WINDOW_WIDTH / 2 - get_text_w(&exitGame_Text) / 2);
    set_text_y(&exitGame_Text, (WINDOW_HEIGHT / 9) * 5);

    bool quit = false;
    SDL_Event e;
    int xMouse, yMouse;

    while (quit == false)
    {
        SDL_RenderClear(window->renderer);

        SDL_RenderCopy(window->renderer, background, NULL, &background_rect);

        mouse_hover(xMouse, yMouse, &newGame_Text);
        mouse_hover(xMouse, yMouse, &leaderboard_Text);

        mouse_hover(xMouse, yMouse, &exitGame_Text);

        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_MOUSEMOTION)
            {
                SDL_GetMouseState(&xMouse, &yMouse);
            }
            if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                if (is_mouse_hover(xMouse, yMouse, get_text_rectangle(&newGame_Text)))
                {
                    set_menu_texture_small(get_text_rectangle(&newGame_Text), get_text_texture(&newGame_Text));
                    quit = true;
                    is_new_game = true;
                }
                if (is_mouse_hover(xMouse, yMouse, get_text_rectangle(&exitGame_Text)))
                {
                    set_menu_texture_small(get_text_rectangle(&exitGame_Text), get_text_texture(&exitGame_Text));
                    quit = true;
                    *close_request = 1;
                }
                if (is_mouse_hover(xMouse, yMouse, get_text_rectangle(&leaderboard_Text)))
                {
                    set_menu_texture_big(get_text_rectangle(&leaderboard_Text), get_text_texture(&leaderboard_Text));
                    leaderboard(players, window, close_request, font, main_font);
                }
            }
            if (e.type == SDL_QUIT)
            {
                quit = true;
                *close_request = 1;
            }
        }
        SDL_RenderCopy(window->renderer, get_text_texture(&main_Text), NULL, get_text_rectangle(&main_Text));
        SDL_RenderCopy(window->renderer, get_text_texture(&newGame_Text), NULL, get_text_rectangle(&newGame_Text));
        SDL_RenderCopy(window->renderer, get_text_texture(&leaderboard_Text), NULL, get_text_rectangle(&leaderboard_Text));
        SDL_RenderCopy(window->renderer, get_text_texture(&exitGame_Text), NULL, get_text_rectangle(&exitGame_Text));

        SDL_RenderPresent(window->renderer);
    }
    SDL_Delay(200);
    if (is_new_game)
    {
        new_game(players, font, main_font, window, close_request);
    }
}

void new_game(Players *players, TTF_Font *font, TTF_Font *main_font, SDL_Context *window, int *close_request)
{

    bool play1 = false;

    SDL_Texture *background = IMG_LoadTexture(window->renderer, "../Assets/background_empty.png");

    char player_path[500] = "../Assets/Player/";

    SDL_Rect background_rect;
    background_rect.x = 0;
    background_rect.y = 0;
    SDL_QueryTexture(background, NULL, NULL, &background_rect.w, &background_rect.h);

    char main_text[100] = "choose character";
    char playButton_text[100] = "Play";
    SDL_Color RGB_WHITE = {255, 255, 255};

    // Icons
    Icon icons[4];
    int player_count = 0;

    init_Icon(&icons[0], 0, RED, window, font);
    init_Icon(&icons[1], 1, BLUE, window, font);
    init_Icon(&icons[2], 2, GREEN, window, font);
    init_Icon(&icons[3], 3, ORANGE, window, font);

    // Title
    Text main_Text;
    init_Text(&main_Text, RGB_WHITE, main_font, main_text, window);
    set_text_x(&main_Text, WINDOW_WIDTH / 2 - get_text_w(&main_Text) / 2);
    set_text_y(&main_Text, (WINDOW_HEIGHT / 15));

    Text playButton_Text;
    init_Text(&playButton_Text, RGB_WHITE, main_font, playButton_text, window);
    set_text_x(&playButton_Text, WINDOW_WIDTH / 2 - get_text_w(&playButton_Text) / 2);
    set_text_y(&playButton_Text, (WINDOW_HEIGHT / 15) * 13);

    bool quit = false;
    SDL_Event e;
    int xMouse, yMouse;

    while (quit == false)
    {
        player_count = 0;
        for (int i = 0; i < 4; i++)
        {
            mouse_hover(xMouse, yMouse, get_icon_player_arrow_left(&icons[i]));
            mouse_hover(xMouse, yMouse, get_icon_player_arrow_right(&icons[i]));
            mouse_hover(xMouse, yMouse, get_icon_icon_arrow_left(&icons[i]));
            mouse_hover(xMouse, yMouse, get_icon_icon_arrow_right(&icons[i]));
            if (get_icon_type(&icons[i]) == PLAYER)
            {
                player_count += 1;
            }
        }
        mouse_hover(xMouse, yMouse, &playButton_Text);

        SDL_RenderClear(window->renderer);

        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_MOUSEMOTION)
            {
                SDL_GetMouseState(&xMouse, &yMouse);
            }
            if (e.type == SDL_MOUSEBUTTONDOWN)
            {

                for (int i = 0; i < 4; i++)
                {

                    if (is_mouse_hover(xMouse, yMouse, get_text_rectangle(get_icon_player_arrow_left(&icons[i]))))
                    {
                        set_menu_texture_small(get_text_rectangle(get_icon_player_arrow_left(&icons[i])), get_text_texture(get_icon_player_arrow_left(&icons[i])));
                        set_text_is_big(get_icon_player_arrow_left(&icons[i]), false);
                        if (get_icon_color(&icons[i]) + 1 > 3)
                        {
                            set_icon_color(&icons[i], 0);
                        }
                        else
                            set_icon_color(&icons[i], get_icon_color(&icons[i]) + 1);
                    }
                    if (is_mouse_hover(xMouse, yMouse, get_text_rectangle(get_icon_player_arrow_right(&icons[i]))))
                    {
                        set_menu_texture_small(get_text_rectangle(get_icon_player_arrow_right(&icons[i])), get_text_texture(get_icon_player_arrow_right(&icons[i])));
                        set_text_is_big(get_icon_player_arrow_right(&icons[i]), false);
                        if (get_icon_color(&icons[i]) == 0)
                        {
                            set_icon_color(&icons[i], 3);
                        }
                        else
                            set_icon_color(&icons[i], get_icon_color(&icons[i]) - 1);
                    }

                    if (is_mouse_hover(xMouse, yMouse, get_text_rectangle(get_icon_icon_arrow_left(&icons[i]))))
                    {
                        set_menu_texture_small(get_text_rectangle(get_icon_icon_arrow_left(&icons[i])), get_text_texture(get_icon_icon_arrow_left(&icons[i])));
                        set_text_is_big(get_icon_icon_arrow_left(&icons[i]), false);
                        if (get_icon_type(&icons[i]) + 1 > 2)
                        {
                            set_icon_type(&icons[i], 0);
                            if (player_count >= 2)
                            {
                                set_icon_type(&icons[i], 1);
                            }
                        }
                        else
                            set_icon_type(&icons[i], get_icon_type(&icons[i]) + 1);
                    }
                    if (is_mouse_hover(xMouse, yMouse, get_text_rectangle(get_icon_icon_arrow_right(&icons[i]))))
                    {
                        set_menu_texture_small(get_text_rectangle(get_icon_icon_arrow_right(&icons[i])), get_text_texture(get_icon_icon_arrow_right(&icons[i])));
                        set_text_is_big(get_icon_icon_arrow_right(&icons[i]), false);
                        if (get_icon_type(&icons[i]) == 0)
                        {
                            set_icon_type(&icons[i], 2);
                        }
                        else
                            set_icon_type(&icons[i], get_icon_type(&icons[i]) - 1);

                        if (get_icon_type(&icons[i]) == 0 && player_count >= 2)
                        {
                            set_icon_type(&icons[i], 2);
                        }
                    }

                    set_icon_player_texture(&icons[i], window);
                    set_icon_texture(&icons[i], window);
                }

                // Play button
                if (is_mouse_hover(xMouse, yMouse, get_text_rectangle(&playButton_Text)))
                {
                    set_menu_texture_small(get_text_rectangle(&playButton_Text), get_text_texture(&playButton_Text));
                    quit = true;

                    for (int i = 0; i < 4; i++)
                    {
                        if (get_icon_type(&icons[i]) == PLAYER)
                        {
                            Player player;
                            init_player(&player, window, i, player_path, get_icon_color(&icons[i]), 0);
                            add_player(players, &player);
                        }
                        else if (get_icon_type(&icons[i]) == ROBOT)
                        {
                            Player player;
                            init_player(&player, window, i, player_path, get_icon_color(&icons[i]), 1);
                            add_player(players, &player);
                        }
                    }
                }
            }
            if (e.type == SDL_QUIT)
            {
                quit = true;
                *close_request = 1;
            }
        }

        SDL_RenderCopy(window->renderer, background, NULL, &background_rect);

        SDL_RenderCopy(window->renderer, get_text_texture(&main_Text), NULL, get_text_rectangle(&main_Text));
        SDL_RenderCopy(window->renderer, get_text_texture(&playButton_Text), NULL, get_text_rectangle(&playButton_Text));

        for (int i = 0; i < 4; i++)
        {
            if (get_icon_type(&icons[i]) != NOTHING)
            {
                SDL_RenderCopy(window->renderer, get_icon_player_texture(&icons[i]), NULL, get_icon_player_rectangle(&icons[i]));
            }
            SDL_RenderCopy(window->renderer, get_text_texture(get_icon_player_arrow_left(&icons[i])), NULL, get_text_rectangle(get_icon_player_arrow_left(&icons[i])));
            SDL_RenderCopy(window->renderer, get_text_texture(get_icon_player_arrow_right(&icons[i])), NULL, get_text_rectangle(get_icon_player_arrow_right(&icons[i])));
            SDL_RenderCopy(window->renderer, get_text_texture(get_icon_icon_arrow_left(&icons[i])), NULL, get_text_rectangle(get_icon_icon_arrow_left(&icons[i])));
            SDL_RenderCopy(window->renderer, get_text_texture(get_icon_icon_arrow_right(&icons[i])), NULL, get_text_rectangle(get_icon_icon_arrow_right(&icons[i])));
            SDL_RenderCopy(window->renderer, get_icon_texture(&icons[i]), NULL, get_icon_rectangle(&icons[i]));
        }

        SDL_RenderPresent(window->renderer);
    }
    SDL_Delay(200);
}

void leaderboard(Players *players, SDL_Context *window, int *close_request, TTF_Font *font, TTF_Font *main_font)
{

    bool play1 = false;
    bool is_new_game = false;

    SDL_Texture *background = IMG_LoadTexture(window->renderer, "../Assets/background_empty.png");

    SDL_Rect background_rect;
    background_rect.x = 0;
    background_rect.y = 0;
    SDL_QueryTexture(background, NULL, NULL, &background_rect.w, &background_rect.h);

    char main_text[100] = "CUBES BATTLE";
    char newGame_text[100] = "New Game";
    char leaderboard_text[100] = "Leaderboard";
    char exitGame_text[100] = "Exit Game";

    SDL_Color RGB_WHITE = {255, 255, 255};

    Text main_Text;
    init_Text(&main_Text, RGB_WHITE, main_font, main_text, window);
    set_text_x(&main_Text, WINDOW_WIDTH / 2 - get_text_w(&main_Text) / 2);
    set_text_y(&main_Text, (WINDOW_HEIGHT / 9));

    // New Game
    Text newGame_Text;
    init_Text(&newGame_Text, RGB_WHITE, font, newGame_text, window);
    set_text_x(&newGame_Text, WINDOW_WIDTH / 2 - get_text_w(&newGame_Text) / 2);
    set_text_y(&newGame_Text, (WINDOW_HEIGHT / 9) * 3);

    // Leadboard
    Text leaderboard_Text;
    init_Text(&leaderboard_Text, RGB_WHITE, font, leaderboard_text, window);
    set_text_x(&leaderboard_Text, WINDOW_WIDTH / 2 - get_text_w(&leaderboard_Text) / 2);
    set_text_y(&leaderboard_Text, (WINDOW_HEIGHT / 9) * 4);

    // Exit Game
    Text exitGame_Text;
    init_Text(&exitGame_Text, RGB_WHITE, font, exitGame_text, window);
    set_text_x(&exitGame_Text, WINDOW_WIDTH / 2 - get_text_w(&exitGame_Text) / 2);
    set_text_y(&exitGame_Text, (WINDOW_HEIGHT / 9) * 5);

    bool quit = false;
    SDL_Event e;
    int xMouse, yMouse;

    while (quit == false)
    {
        SDL_RenderClear(window->renderer);

        SDL_RenderCopy(window->renderer, background, NULL, &background_rect);

        mouse_hover(xMouse, yMouse, &newGame_Text);
        mouse_hover(xMouse, yMouse, &leaderboard_Text);

        mouse_hover(xMouse, yMouse, &exitGame_Text);

        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_MOUSEMOTION)
            {
                SDL_GetMouseState(&xMouse, &yMouse);
            }
            if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                if (is_mouse_hover(xMouse, yMouse, get_text_rectangle(&newGame_Text)))
                {
                    set_menu_texture_small(get_text_rectangle(&newGame_Text), get_text_texture(&newGame_Text));
                    quit = true;
                    is_new_game = true;
                }
                if (is_mouse_hover(xMouse, yMouse, get_text_rectangle(&exitGame_Text)))
                {
                    set_menu_texture_small(get_text_rectangle(&exitGame_Text), get_text_texture(&exitGame_Text));
                    quit = true;
                    *close_request = 1;
                }
                if (is_mouse_hover(xMouse, yMouse, get_text_rectangle(&leaderboard_Text)))
                {
                    set_menu_texture_big(get_text_rectangle(&leaderboard_Text), get_text_texture(&leaderboard_Text));
                    read_from_leaderboard();
                }
            }
            if (e.type == SDL_QUIT)
            {
                quit = true;
                *close_request = 1;
            }
        }
        SDL_RenderCopy(window->renderer, get_text_texture(&main_Text), NULL, get_text_rectangle(&main_Text));
        SDL_RenderCopy(window->renderer, get_text_texture(&newGame_Text), NULL, get_text_rectangle(&newGame_Text));
        SDL_RenderCopy(window->renderer, get_text_texture(&leaderboard_Text), NULL, get_text_rectangle(&leaderboard_Text));
        SDL_RenderCopy(window->renderer, get_text_texture(&exitGame_Text), NULL, get_text_rectangle(&exitGame_Text));

        SDL_RenderPresent(window->renderer);
    }
    SDL_Delay(200);
}

void mouse_hover(int xMouse, int yMouse, Text *text)
{
    if (is_mouse_hover(xMouse, yMouse, get_text_rectangle(text)) && get_text_is_big(text) == false)
    {

        set_menu_texture_big(get_text_rectangle(text), get_text_texture(text));

        set_text_is_big(text, true);
    }
    else if (is_mouse_hover(xMouse, yMouse, get_text_rectangle(text)) == false && get_text_is_big(text) == true)
    {
        set_menu_texture_small(get_text_rectangle(text), get_text_texture(text));
        set_text_is_big(text, false);
    }
}

bool is_mouse_hover(int xMouse, int yMouse, SDL_Rect *rect)
{
    if (xMouse >= rect->x && xMouse <= rect->x + rect->w && yMouse >= rect->y && yMouse <= rect->y + rect->h)
    {
        return true;
    }
    else
        return false;
}

void set_menu_texture_big(SDL_Rect *rect, SDL_Texture *texture)
{
    int rect_height = rect->h;
    int rect_width = rect->w;
    SDL_QueryTexture(texture, NULL, NULL, &rect->w, &rect->h);
    rect->w *= 1.3;
    rect->h *= 1.3;
    rect->x -= floor((rect->w - rect_width) / 2);
    rect->y -= floor((rect->h - rect_height) / 2);
}

void set_menu_texture_small(SDL_Rect *rect, SDL_Texture *texture)
{
    int rect_height = rect->h;
    int rect_width = rect->w;
    SDL_QueryTexture(texture, NULL, NULL, &rect->w, &rect->h);
    rect->x += floor((rect_width - rect->w) / 2);
    rect->y += floor((rect_height - rect->h) / 2);
}

// SETTERS

void set_text_rectangle(Text *text, SDL_Rect *rect)
{

    text->rect = *rect;
}

void set_text_x(Text *text, double x)
{
    text->rect.x = floor(x);
}

void set_text_y(Text *text, double y)
{
    text->rect.y = floor(y);
}

void set_text_w(Text *text, int w)
{
    text->rect.w = w;
}

void set_text_h(Text *text, int h)
{
    text->rect.h = h;
}

void set_text_surface(Text *text, SDL_Surface *surface)
{
    text->surface = surface;
}

void set_text_texture(Text *text, SDL_Texture *texture)
{
    text->texture = texture;
}

void set_text_font(Text *text, TTF_Font *font)
{
    text->font = font;
}

void set_text_color(Text *text, SDL_Color color)
{
    text->color = color;
}

void set_text_is_big(Text *text, bool is_big)
{
    text->is_text_big = is_big;
}

// Icon
void set_icon_id(Icon *icon, int id)
{
    icon->id = id;
}

void set_icon_rectangle(Icon *icon, SDL_Rect *rect)
{
    icon->rect = *rect;
}

void set_icon_player_rectangle(Icon *icon, SDL_Rect *rect)
{
    icon->player_icon_rect = *rect;
}

void set_icon_x(Icon *icon, double x)
{
    icon->rect.x = floor(x);
}

void set_icon_y(Icon *icon, double y)
{
    icon->rect.y = floor(y);
}

void set_icon_w(Icon *icon, int w)
{
    icon->rect.w = w;
}

void set_icon_h(Icon *icon, int h)
{
    icon->rect.h = h;
}

void set_icon_player_w(Icon *icon, int w)
{
    icon->player_icon_rect.w = w;
}

void set_icon_player_h(Icon *icon, int h)
{
    icon->player_icon_rect.h = h;
}

void set_icon_texture(Icon *icon, SDL_Context *window)
{
    char name[50] = "";
    char image_path[200] = "";
    switch (get_icon_type(icon))
    {
    case PLAYER:
        strcpy(name, "player_icon");
        break;

    case ROBOT:
        strcpy(name, "robot_icon");
        break;

    case NOTHING:
        strcpy(name, "cross_icon");
        break;
    default:
        strcpy(name, "cross_icon");
        break;
    }

    sprintf(image_path, "../Assets/Icons/%s.png", name);

    SDL_Texture *tex = IMG_LoadTexture(window->renderer, image_path);
    assert(tex);

    icon->texture = tex;
}

void set_icon_player_texture(Icon *icon, SDL_Context *window)
{
    char color[50] = "";
    char image_path[200] = "";
    switch (get_icon_color(icon))
    {
    case RED:
        strcpy(color, "red");
        break;

    case BLUE:
        strcpy(color, "blue");
        break;

    case GREEN:
        strcpy(color, "green");
        break;

    case ORANGE:
        strcpy(color, "orange");
        break;

    default:
        strcpy(color, "orange");
        break;
    }

    sprintf(image_path, "../Assets/Player/%s_bulanek_up.png", color);

    SDL_Texture *tex = IMG_LoadTexture(window->renderer, image_path);
    assert(tex);

    icon->player_icon_texture = tex;
}

void set_icon_player_arrow_left(Icon *icon, Text text)
{
    icon->player_arrow_left = text;
}

void set_icon_player_arrow_right(Icon *icon, Text text)
{
    icon->player_arrow_right = text;
}

void set_icon_icon_arrow_left(Icon *icon, Text text)
{
    icon->icon_arrow_left = text;
}

void set_icon_icon_arrow_right(Icon *icon, Text text)
{
    icon->icon_arrow_right = text;
}

void set_icon_color(Icon *icon, Color color)
{
    icon->color = color;
}

void set_icon_type(Icon *icon, Icon_type type)
{
    icon->type = type;
}

// GETTERS
int get_text_x(Text *text)
{
    return text->rect.x;
}

int get_text_y(Text *text)
{
    return text->rect.y;
}

int get_text_w(Text *text)
{
    return text->rect.w;
}

int get_text_h(Text *text)
{
    return text->rect.h;
}

SDL_Color get_text_color(Text *text)
{
    return text->color;
}

SDL_Surface *get_text_surface(Text *text)
{
    return text->surface;
}
SDL_Texture *get_text_texture(Text *text)
{
    return text->texture;
}

SDL_Rect *get_text_rectangle(Text *text)
{
    return &text->rect;
}

TTF_Font *get_text_font(Text *text)
{
    return text->font;
}

bool get_text_is_big(Text *text)
{
    return text->is_text_big;
}

// Icon
int get_icon_id(Icon *icon)
{
    return icon->id;
}
int get_icon_x(Icon *icon)
{
    return icon->rect.x;
}

int get_icon_y(Icon *icon)
{
    return icon->rect.y;
}

int get_icon_w(Icon *icon)
{
    return icon->rect.w;
}

int get_icon_h(Icon *icon)
{
    return icon->rect.h;
}

Color get_icon_color(Icon *icon)
{
    return icon->color;
}

SDL_Texture *get_icon_texture(Icon *icon)
{
    return icon->texture;
}

SDL_Rect *get_icon_rectangle(Icon *icon)
{
    return &icon->rect;
}

SDL_Texture *get_icon_player_texture(Icon *icon)
{
    return icon->player_icon_texture;
}

SDL_Rect *get_icon_player_rectangle(Icon *icon)
{
    return &icon->player_icon_rect;
}

Icon_type get_icon_type(Icon *icon)
{
    return icon->type;
}

Text *get_icon_player_arrow_left(Icon *icon)
{
    return &icon->player_arrow_left;
}

Text *get_icon_player_arrow_right(Icon *icon)
{
    return &icon->player_arrow_right;
}

Text *get_icon_icon_arrow_left(Icon *icon)
{
    return &icon->icon_arrow_left;
}

Text *get_icon_icon_arrow_right(Icon *icon)
{
    return &icon->icon_arrow_right;
}
