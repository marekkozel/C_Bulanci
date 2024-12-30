
#include "player.h"

void init_players(Players *players)
{
    players->count_players = 0;
    players->players = (Player *)malloc(4 * sizeof(Player));
}

void add_player(Players *players, Player *player)
{
    players->players[players->count_players] = *player;
    players->count_players += 1;
}

void init_player(Player *player, SDL_Context *window, int id, char path[100], Color color, int type)
{

    set_player_id(player, id);

    set_player_color(player, color);
    set_player_direction(player, 0, -1);
    set_player_texture(player, window, path);
    set_player_health(player, 100);
    set_player_velovity_x(player, 0);
    set_player_velovity_y(player, 0);
    set_player_velovity_x(player, 0);
    set_player_friction_x(player, 0);
    set_player_friction_y(player, 0);
    set_player_multiplier_x(player, 1);
    set_player_multiplier_y(player, 1);
    set_player_power(player, GUN);
    set_player_score(player, 0);
    set_player_type(player, type);

    SDL_Rect *dest = (SDL_Rect *)malloc(sizeof(SDL_Rect));

    SDL_QueryTexture(player->texture, NULL, NULL, &dest->w, &dest->h);
    dest->w *= 5;
    dest->h *= 5;
    switch (id)
    {
    case 0:
        dest->x = 181;
        dest->y = 184;
        break;
    case 1:
        dest->x = 181;
        dest->y = 864;
        break;
    case 2:
        dest->x = 1701;
        dest->y = 184;
        break;
    case 3:
        dest->x = 1701;
        dest->y = 864;
        break;

    default:
        break;
    }

    set_player_rectangle(player, dest);
}

void move_player(Player *player, double delta_time, Players *players, Obstacles *obstacles, dynarray *power_ups, dynarray *projectils, SDL_Context *window, double time)
{
    int respawn_timer = 3;
    if (get_player_dead_time(player) + respawn_timer < time && get_player_heath(player) <= 0)
    {
        respawn_player(players, player, obstacles);
    }

    check_power_up_time(player, time);

    set_player_multiplier_x(player, 1);
    set_player_multiplier_y(player, 1);

    // Colisions
    detect_players_collisions(player, players);
    detect_boarders_collisions(player);
    detect_obstacles_collisions(player, obstacles);
    detect_power_up_collision(player, power_ups, time);
    detect_projectils_collision(players, player, projectils, obstacles, window, time);

    // Movement
    double velocity_x = get_player_velocity_x(player);
    double velocity_y = get_player_velocity_y(player);

    set_player_x(player, (double)get_player_x(player) + (velocity_x * delta_time) * get_player_multiplier_x(player));
    set_player_y(player, (double)get_player_y(player) + (velocity_y * delta_time) * get_player_multiplier_y(player));

    if (velocity_x > -55 && velocity_x < 55)
    {
        velocity_x = 0;
    }
    else if (velocity_x > 0)
    {
        velocity_x -= player->friction_x;
    }
    else if (velocity_x < 0)
    {
        velocity_x += player->friction_x;
    }

    if (velocity_y > -55 && velocity_y < 55)
    {
        velocity_y = 0;
    }
    else if (velocity_y > 0)
    {
        velocity_y -= player->friction_y;
    }
    else if (velocity_y < 0)
    {
        velocity_y += player->friction_y;
    }
    set_player_velovity_x(player, velocity_x);
    set_player_velovity_y(player, velocity_y);
}

void respawn_player(Players *players, Player *player, Obstacles *obsatcles)
{
    SDL_Rect *dest = (SDL_Rect *)malloc(sizeof(SDL_Rect));

    int can_spawn = 1;
    while (can_spawn)
    {
        SDL_QueryTexture(player->texture, NULL, NULL, &dest->w, &dest->h);
        dest->w *= 5;
        dest->h *= 5;
        dest->x = 20 + rand() % 1840;
        dest->y = 20 + rand() % 1000;

        can_spawn = 0;

        for (int i = 0; i < obsatcles->count_obstacles; i++)
        {
            if (SDL_HasIntersection(dest, obsatcles->obstacles[i].rectangle))
            {
                can_spawn = 1;
                break;
            }
        }
        for (int i = 0; i < players->count_players; i++)
        {
            if (SDL_HasIntersection(dest, &players->players[i].rectangle))
            {
                can_spawn = 1;
                break;
            }
        }
    }
    set_player_rectangle(player, dest);
    set_player_health(player, 100);
    set_player_power(player, GUN);
}

void animate_player(Player *player, SDL_Context *window, char *path)
{
    if (get_player_texture(player) != NULL)
    {
        SDL_DestroyTexture(get_player_texture(player));
    }
    set_player_texture(player, window, path);
}

void detect_players_collisions(Player *player, Players *players)
{

    for (int i = 0; i < players->count_players; i++)
    {
        if (get_player_id(player) != players->players[i].id && SDL_HasIntersection(&player->rectangle, &players->players[i].rectangle))
        {

            if (get_player_y(player) < get_player_y(&players->players[i]) + get_player_h(&players->players[i]) - 10 && get_player_y(player) + get_player_h(player) > get_player_y(&players->players[i]) + 10)
            {

                if (get_player_x(&players->players[i]) <= get_player_x(player) + get_player_w(player) && get_player_x(player) > get_player_x(&players->players[i]) + (get_player_w(&players->players[i]) / 2))
                {
                    if (get_player_velocity_x(player) < 0)
                    {
                        set_player_multiplier_x(player, 0);
                    }
                }
                else if (get_player_x(player) + get_player_w(player) >= get_player_x(&players->players[i]))
                {
                    if (get_player_velocity_x(player) > 0)
                    {
                        set_player_multiplier_x(player, 0);
                    }
                }
            }
            else
            {
                if (get_player_y(&players->players[i]) <= get_player_y(player) + get_player_h(player) && get_player_y(player) > get_player_y(&players->players[i]) + (get_player_h(&players->players[i]) / 2))
                {
                    if (get_player_velocity_y(player) < 0)
                    {
                        set_player_multiplier_y(player, 0);
                    }
                }
                else if (get_player_y(player) + get_player_h(player) >= get_player_y(&players->players[i]))
                {
                    if (get_player_velocity_y(player) > 0)
                    {
                        set_player_multiplier_y(player, 0);
                    }
                }
            }
        }
    }
}

void detect_boarders_collisions(Player *player)
{
    if (get_player_x(player) <= 0)
        set_player_x(player, 0);
    if (get_player_y(player) <= 0)
        set_player_y(player, 0);

    if (get_player_x(player) >= WINDOW_WIDTH - get_player_w(player))
        set_player_x(player, WINDOW_WIDTH - get_player_w(player));
    if (get_player_y(player) >= WINDOW_HEIGHT - get_player_h(player))
        set_player_y(player, WINDOW_HEIGHT - get_player_h(player));
}

void detect_obstacles_collisions(Player *player, Obstacles *obstacles)
{
    for (int i = 0; i < obstacles->count_obstacles; i++)
    {
        if (SDL_HasIntersection(get_player_rectangle(player), obstacles->obstacles[i].rectangle))
        {

            if (get_player_y(player) < get_obstacle_y(&obstacles->obstacles[i]) + get_obstacle_h(&obstacles->obstacles[i]) - 10 && get_player_y(player) + get_player_h(player) > get_obstacle_y(&obstacles->obstacles[i]) + 10)
            {

                if (get_player_x(player) <= get_obstacle_x(&obstacles->obstacles[i]) + get_obstacle_w(&obstacles->obstacles[i]) && get_player_x(player) > get_obstacle_x(&obstacles->obstacles[i]) + (get_obstacle_w(&obstacles->obstacles[i]) / 2))
                {
                    if (get_player_velocity_x(player) < 0)
                    {
                        set_player_multiplier_x(player, 0);
                    }
                }
                else if (get_player_x(player) + get_player_w(player) >= get_obstacle_x(&obstacles->obstacles[i]))
                {
                    if (get_player_velocity_x(player) > 0)
                    {
                        set_player_multiplier_x(player, 0);
                    }
                }
            }
            else
            {
                if (get_player_y(player) <= get_obstacle_y(&obstacles->obstacles[i]) + get_obstacle_h(&obstacles->obstacles[i]) && get_player_y(player) > get_obstacle_y(&obstacles->obstacles[i]) + (get_obstacle_h(&obstacles->obstacles[i]) / 2))
                {
                    if (get_player_velocity_y(player) < 0)
                    {
                        set_player_multiplier_y(player, 0);
                    }
                }
                else if (get_player_y(player) + get_player_h(player) >= get_obstacle_y(&obstacles->obstacles[i]))
                {
                    if (get_player_velocity_y(player) > 0)
                    {
                        set_player_multiplier_y(player, 0);
                    }
                }
            }
        }
    }
}

void detect_power_up_collision(Player *player, dynarray *power_ups, double time)
{
    for (int i = 0; i < power_ups->size; i++)
    {
        Power_up *power_up;
        power_up = dynarray_get(power_ups, i);

        if (SDL_HasIntersection(&player->rectangle, power_up->rectangle))
        {
            set_player_power(player, get_power_up_power(power_up));
            set_player_power_time(player, time);
            dynarray_remove(power_ups, power_up);
        }
    }
}

void check_power_up_time(Player *player, double time)
{
    int power_up_time = 8;
    if (get_player_power_time(player) + power_up_time < time)
    {
        set_player_power(player, GUN);
    }
}

void detect_projectils_collision(Players *players, Player *player, dynarray *projectils, Obstacles *obstacles, SDL_Context *window, double time)
{
    for (int i = 0; i < projectils->size; i++)
    {
        Projectil *projectil;
        projectil = dynarray_get(projectils, i);

        if (SDL_HasIntersection(&player->rectangle, projectil->rectangle) && get_projectil_player_id(projectil) != get_player_id(player))
        {

            if (get_projectil_id(projectil) == ROCKET)
            {
                rocket_explosion(projectil, projectils, window, get_projectil_player_id(projectil), get_projectil_x(projectil), get_projectil_y(projectil), time);
            }
            else if (get_projectil_id(projectil) == GUN)
            {
                set_player_health(player, get_player_heath(player) - 50);
            }
            else if (get_projectil_id(projectil) == MINE)
            {
                set_player_health(player, get_player_heath(player) - 150);
            }
            else if (get_projectil_id(projectil) == SHOTGUN)
            {
                set_player_health(player, get_player_heath(player) - 40);
            }

            set_projectil_w(projectil, 0);
            set_projectil_h(projectil, 0);

            if (get_player_heath(player) <= 0)
            {
                set_player_w(player, 0);
                set_player_h(player, 0);
                set_player_dead_time(player, time);
                for (int i = 0; i < players->count_players; i++)
                {
                    if (get_player_id(&players->players[i]) == get_projectil_player_id(projectil))
                    {
                        add_player_score(&players->players[i], 1);
                    }
                }
            }
        }
    }
}

void spawn_projectil(Player *player, dynarray *projectils, SDL_Context *window, double timer)
{
    if (get_player_heath(player) > 0)
    {
        double last_time = 0;
        for (int i = 0; i < projectils->size; i++)
        {
            Projectil *projectil;
            projectil = dynarray_get(projectils, i);
            if (get_player_id(player) == get_projectil_player_id(projectil))
            {
                last_time = get_projectil_spawn_time(projectil);
            }
        }

        char path[100] = "";
        switch (get_player_power(player))
        {
        case GUN:
            if (timer - last_time >= 0.5)
            {
                double self_destruct = 1.5;
                strcpy(path, "../Assets/Projectils/bullet.png");
                init_projectil(projectils, window, GUN, get_player_id(player), get_player_x(player) + (get_player_w(player) / 2), get_player_y(player) + (get_player_h(player) / 2), 1000, (double)get_player_direction_x(player), (double)get_player_direction_y(player), timer, self_destruct, path);
            }

            break;
        case SHOTGUN:

            if (timer - last_time >= 0.75)
            {
                double self_destruct = 0.35;
                strcpy(path, "../Assets/Projectils/bullet.png");
                if (get_player_direction_x(player) == 1 || get_player_direction_x(player) == -1)
                {
                    init_projectil(projectils, window, SHOTGUN, get_player_id(player), get_player_x(player) + (get_player_w(player) / 2), get_player_y(player) + (get_player_h(player) / 2), 1200, (double)get_player_direction_x(player), 0.25, timer, self_destruct, path);
                    init_projectil(projectils, window, SHOTGUN, get_player_id(player), get_player_x(player) + (get_player_w(player) / 2), get_player_y(player) + (get_player_h(player) / 2), 1200, (double)get_player_direction_x(player), -0.25, timer, self_destruct, path);

                    init_projectil(projectils, window, SHOTGUN, get_player_id(player), get_player_x(player) + (get_player_w(player) / 2), get_player_y(player) + (get_player_h(player) / 2), 1200, (double)get_player_direction_x(player), 0.5, timer, self_destruct, path);
                    init_projectil(projectils, window, SHOTGUN, get_player_id(player), get_player_x(player) + (get_player_w(player) / 2), get_player_y(player) + (get_player_h(player) / 2), 1200, (double)get_player_direction_x(player), -0.5, timer, self_destruct, path);
                }
                else if (get_player_direction_y(player) == 1 || get_player_direction_y(player) == -1)
                {
                    init_projectil(projectils, window, SHOTGUN, get_player_id(player), get_player_x(player) + (get_player_w(player) / 2), get_player_y(player) + (get_player_h(player) / 2), 1200, 0.25, (double)get_player_direction_y(player), timer, self_destruct, path);
                    init_projectil(projectils, window, SHOTGUN, get_player_id(player), get_player_x(player) + (get_player_w(player) / 2), get_player_y(player) + (get_player_h(player) / 2), 1200, -0.25, (double)get_player_direction_y(player), timer, self_destruct, path);

                    init_projectil(projectils, window, SHOTGUN, get_player_id(player), get_player_x(player) + (get_player_w(player) / 2), get_player_y(player) + (get_player_h(player) / 2), 1200, 0.5, (double)get_player_direction_y(player), timer, self_destruct, path);
                    init_projectil(projectils, window, SHOTGUN, get_player_id(player), get_player_x(player) + (get_player_w(player) / 2), get_player_y(player) + (get_player_h(player) / 2), 1200, -0.5, (double)get_player_direction_y(player), timer, self_destruct, path);
                }

                init_projectil(projectils, window, SHOTGUN, get_player_id(player), get_player_x(player) + (get_player_w(player) / 2), get_player_y(player) + (get_player_h(player) / 2), 1200, get_player_direction_x(player), get_player_direction_y(player), timer, self_destruct, path);
            }
            break;
        case ROCKET:
            if (timer - last_time >= 1)
            {
                double self_destruct = 5;
                strcpy(path, "../Assets/Projectils/rocket_bullet.png");
                init_projectil(projectils, window, ROCKET, get_player_id(player), get_player_x(player) + (get_player_w(player) / 2), get_player_y(player) + (get_player_h(player) / 2), 500, (double)get_player_direction_x(player), (double)get_player_direction_y(player), timer, self_destruct, path);
            }
            break;
        case MINE:
            if (timer - last_time >= 1.25)
            {
                double self_destruct = 30;
                strcpy(path, "../Assets/Projectils/mine.png");
                init_projectil(projectils, window, MINE, get_player_id(player), get_player_x(player) + (get_player_w(player) / 2), get_player_y(player) + (get_player_h(player) / 2), 0, (double)get_player_direction_x(player), (double)get_player_direction_y(player), timer, self_destruct, path);
            }
            break;
        default:
            break;
        }
    }
}

// ______________________________________________________________________

void add_player_score(Player *player, int score)
{
    player->score += score;
}

void set_player_score(Player *player, int score)
{
    player->score = score;
}

void set_player_type(Player *player, int type)
{
    player->type = type;
}

void set_player_friction_x(Player *player, int friction)
{
    player->friction_x = friction;
}

void set_player_friction_y(Player *player, int friction)
{
    player->friction_y = friction;
}

void set_player_id(Player *player, int id)
{
    player->id = id;
}

void set_player_rectangle(Player *player, SDL_Rect *rect)
{
    player->rectangle = *rect;
}

void set_player_x(Player *player, double x)
{
    player->rectangle.x = floor(x);
}

void set_player_y(Player *player, double y)
{
    player->rectangle.y = floor(y);
}

void set_player_w(Player *player, int w)
{
    player->rectangle.w = w;
}

void set_player_h(Player *player, int h)
{
    player->rectangle.h = h;
}

void set_player_texture(Player *player, SDL_Context *window, char *path)
{
    char color[100] = "";
    char direction[100] = "";
    char image_path[500] = "";
    switch (get_player_color(player))
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

    if (get_player_direction_x(player) > 0)
    {
        strcpy(direction, "right");
    }
    else if (get_player_direction_x(player) < 0)
    {
        strcpy(direction, "left");
    }
    else if (get_player_direction_y(player) > 0)
    {
        strcpy(direction, "down");
    }
    else if (get_player_direction_y(player) < 0)
    {
        strcpy(direction, "up");
    }
    else
    {
        strcpy(direction, "up");
    }

    sprintf(image_path, "%s%s_bulanek_%s.png", path, color, direction);

    SDL_Texture *tex = IMG_LoadTexture(window->renderer, image_path);
    assert(tex);

    SDL_SetTextureAlphaMod(tex, 55 + (200 * get_player_heath(player) / 100));

    player->texture = tex;
}

void set_player_health(Player *player, int health)
{
    player->health = health;
}

void set_player_velovity_x(Player *player, double velocity_x)
{

    player->velocity_x = velocity_x;
}

void set_player_velovity_y(Player *player, double velocity_y)
{
    player->velocity_y = velocity_y;
}

void set_player_multiplier_x(Player *player, int multiplier)
{
    player->multiplier_x = multiplier;
}

void set_player_multiplier_y(Player *player, int multiplier)
{
    player->multiplier_y = multiplier;
}

void set_player_direction(Player *player, int direction_x, int direction_y)
{
    player->direction_x = direction_x;
    player->direction_y = direction_y;
}

void set_player_color(Player *player, Color color)
{
    player->color = color;
}

void set_player_power(Player *player, Power power)
{
    player->power = power;
}

void set_player_power_time(Player *player, double time)
{
    player->power_time = time;
}

void set_player_dead_time(Player *player, double time)
{
    player->dead_time = time;
}

// Getters
int get_player_id(Player *player)
{
    return player->id;
}

int get_player_type(Player *player)
{
    return player->type;
}

double get_player_velocity_x(Player *player)
{
    return player->velocity_x;
}

double get_player_velocity_y(Player *player)
{
    return player->velocity_y;
}

SDL_Rect *get_player_rectangle(Player *player)
{
    return &player->rectangle;
}

int get_player_x(Player *player)
{
    return player->rectangle.x;
}

int get_player_y(Player *player)
{
    return player->rectangle.y;
}

int get_player_w(Player *player)
{
    return player->rectangle.w;
}

int get_player_h(Player *player)
{
    return player->rectangle.h;
}

int get_player_multiplier_x(Player *player)
{
    return player->multiplier_x;
}

int get_player_multiplier_y(Player *player)
{
    return player->multiplier_y;
}

int get_player_direction_x(Player *player)
{
    return player->direction_x;
}

int get_player_direction_y(Player *player)
{
    return player->direction_y;
}

int get_player_heath(Player *player)
{
    return player->health;
}

Color get_player_color(Player *player)
{
    return player->color;
}

Power get_player_power(Player *player)
{
    return player->power;
}

double get_player_power_time(Player *player)
{
    return player->power_time;
}

int get_player_score(Player *player)
{
    return player->score;
}

double get_player_dead_time(Player *player)
{
    return player->dead_time;
}

SDL_Texture *get_player_texture(Player *player)
{
    return player->texture;
}