#include "bot.h"

void bot_logic(Players *players, Player *player, SDL_Context *window, dynarray *projectils, dynarray *power_ups, Obstacles *obstacles, double time)
{

    int clossest_player_id = -1;
    int clossest_power_up_id = -1;
    int distance_x = 0;
    int distance_y = 0;
    int power_up_distance_x = 0;
    int power_up_distance_y = 0;
    int prev_distance_x = WINDOW_WIDTH;
    int prev_distance_y = WINDOW_HEIGHT;

    // clossest player
    for (int i = 0; i < players->count_players; i++)
    {
        if (get_player_id(&players->players[i]) != get_player_id(player) && get_player_heath(&players->players[i]) > 0)
        {
            distance_x = abs(get_player_x(&players->players[i]) - get_player_x(player));
            distance_y = abs(get_player_y(&players->players[i]) - get_player_y(player));
            if ((distance_x + distance_y) < (prev_distance_x + prev_distance_y))
            {
                clossest_player_id = get_player_id(&players->players[i]);
            }
            prev_distance_x = distance_x;
            prev_distance_y = distance_y;
        }
    }

    // clossest power_up
    for (int i = 0; i < power_ups->size; i++)
    {
        distance_x = abs(get_power_up_x(power_ups->items[i]) - get_player_x(player));
        distance_y = abs(get_power_up_y(power_ups->items[i]) - get_player_y(player));
        if ((distance_x + distance_y) < (prev_distance_x + prev_distance_y))
        {
            clossest_power_up_id = i;
        }
        prev_distance_x = distance_x;
        prev_distance_y = distance_y;
    }

    // target
    if (clossest_player_id != -1)
    {
        distance_x = abs(get_player_x(&players->players[clossest_player_id]) - get_player_x(player));
        distance_y = abs(get_player_y(&players->players[clossest_player_id]) - get_player_y(player));
    }
    else
    {
        distance_x = WINDOW_WIDTH;
        distance_y = WINDOW_HEIGHT;
    }

    if (clossest_power_up_id != -1)
    {
        power_up_distance_x = abs(get_power_up_x(power_ups->items[clossest_power_up_id]) - get_player_x(player));
        power_up_distance_y = abs(get_power_up_y(power_ups->items[clossest_power_up_id]) - get_player_y(player));
    }
    else
    {
        power_up_distance_x = WINDOW_WIDTH;
        power_up_distance_y = WINDOW_HEIGHT;
    }

    if ((distance_x + distance_y) > (power_up_distance_x + power_up_distance_y) && clossest_power_up_id != -1)
    {
        // Power up navigation

        if (get_player_y(player) < get_power_up_y(power_ups->items[clossest_power_up_id]) + get_power_up_h(power_ups->items[clossest_power_up_id]) && get_player_y(player) + get_player_h(player) > get_power_up_y(power_ups->items[clossest_power_up_id]))
        {

            if (get_player_x(player) <= get_power_up_x(power_ups->items[clossest_power_up_id]) + get_power_up_w(power_ups->items[clossest_power_up_id]))
            {
                set_player_friction_x(player, 0);
                set_player_velovity_x(player, BOT_SPEED);
                set_player_friction_y(player, FRICTION);
                set_player_direction(player, 1, 0);
            }
            else if (get_player_x(player) + get_player_w(player) >= get_power_up_x(power_ups->items[clossest_power_up_id]))
            {
                set_player_friction_x(player, 0);
                set_player_velovity_x(player, -BOT_SPEED);
                set_player_friction_y(player, FRICTION);
                set_player_direction(player, -1, 0);
            }
        }
        else
        {
            if (get_player_y(player) <= get_power_up_y(power_ups->items[clossest_power_up_id]) + get_power_up_h(power_ups->items[clossest_power_up_id]))
            {

                set_player_friction_y(player, 0);
                set_player_velovity_y(player, BOT_SPEED);
                set_player_friction_x(player, FRICTION);
                set_player_direction(player, 0, 1);
            }
            else if (get_player_y(player) + get_player_h(player) >= get_power_up_y(power_ups->items[clossest_power_up_id]))
            {

                set_player_friction_y(player, 0);
                set_player_velovity_y(player, -BOT_SPEED);
                set_player_friction_x(player, FRICTION);
                set_player_direction(player, 0, -1);
            }
        }
    }
    else if ((distance_x + distance_y) < (power_up_distance_x + power_up_distance_y) && clossest_player_id != -1)
    {
        // Player navigation
        if (get_player_y(player) < get_player_y(&players->players[clossest_player_id]) + get_player_h(&players->players[clossest_player_id]) && get_player_y(player) + get_player_h(player) > get_player_y(&players->players[clossest_player_id]))
        {

            if (get_player_x(player) + get_player_w(player) / 2 > get_player_x(&players->players[clossest_player_id]) && get_player_x(player) + get_player_w(player) / 2 < get_player_x(&players->players[clossest_player_id]) + get_player_w(&players->players[clossest_player_id]))
            {
                // Is in y row
                if (get_player_y(player) + 10 >= get_player_y(&players->players[clossest_player_id]) + get_player_h(&players->players[clossest_player_id]))
                {
                    // Is under
                    set_player_friction_y(player, 0);
                    set_player_velovity_y(player, -BOT_SPEED);
                    set_player_velovity_x(player, 0);
                    set_player_friction_x(player, FRICTION);
                    set_player_direction(player, 0, -1);
                }
                else if (get_player_y(player) + get_player_w(player) - 10 <= get_player_y(&players->players[clossest_player_id]))
                {
                    // Is above
                    set_player_friction_y(player, 0);
                    set_player_velovity_y(player, BOT_SPEED);
                    set_player_velovity_x(player, 0);
                    set_player_friction_x(player, FRICTION);
                    set_player_direction(player, 0, 1);
                }
            }
            else if (get_player_y(player) + get_player_h(player) / 2 > get_player_y(&players->players[clossest_player_id]) && get_player_y(player) + get_player_h(player) / 2 < get_player_y(&players->players[clossest_player_id]) + get_player_h(&players->players[clossest_player_id]))
            {
                // Is in x row
                if (get_player_x(player) + get_player_w(player) - 10 <= get_player_x(&players->players[clossest_player_id]))
                {
                    // Is Left
                    set_player_friction_x(player, 0);
                    set_player_velovity_x(player, BOT_SPEED);
                    set_player_friction_y(player, FRICTION);
                    set_player_direction(player, 1, 0);
                }
                else if (get_player_x(player) + 10 >= get_player_x(&players->players[clossest_player_id]) + get_player_w(&players->players[clossest_player_id]))
                {
                    // Is Right
                    set_player_friction_x(player, 0);
                    set_player_velovity_x(player, -BOT_SPEED);
                    set_player_friction_y(player, FRICTION);
                    set_player_direction(player, -1, 0);
                }
            }
            else if (get_player_x(player) + get_player_w(player) > get_player_x(&players->players[clossest_player_id]) && get_player_x(player) < get_player_x(&players->players[clossest_player_id]) + get_player_w(&players->players[clossest_player_id]))
            {
                // Is close to y row
                if (get_player_x(player) <= get_player_x(&players->players[clossest_player_id]) + get_player_w(&players->players[clossest_player_id]) / 2)
                {
                    set_player_friction_x(player, 0);
                    set_player_velovity_x(player, BOT_SPEED);
                    set_player_friction_y(player, FRICTION);
                    set_player_direction(player, 1, 0);
                }
                else if (get_player_x(player) >= get_player_x(&players->players[clossest_player_id]) + get_player_w(&players->players[clossest_player_id]) / 2)
                {
                    set_player_friction_x(player, 0);
                    set_player_velovity_x(player, -BOT_SPEED);
                    set_player_friction_y(player, FRICTION);
                    set_player_direction(player, -1, 0);
                }
            }
            else if (get_player_y(player) + get_player_h(player) > get_player_y(&players->players[clossest_player_id]) && get_player_y(player) < get_player_y(&players->players[clossest_player_id]) + get_player_h(&players->players[clossest_player_id]))
            {
                // Is close to x row
                if (get_player_y(player) <= get_player_y(&players->players[clossest_player_id]) + get_player_h(&players->players[clossest_player_id]) / 2)
                {
                    // Is above
                    set_player_friction_y(player, 0);
                    set_player_velovity_y(player, BOT_SPEED);
                    set_player_velovity_x(player, 0);
                    set_player_friction_x(player, FRICTION);
                    set_player_direction(player, 0, 1);
                }
                else if (get_player_y(player) >= get_player_y(&players->players[clossest_player_id]) + get_player_h(&players->players[clossest_player_id]) / 2)
                {
                    // Is under
                    set_player_friction_y(player, 0);
                    set_player_velovity_y(player, -BOT_SPEED);
                    set_player_velovity_x(player, 0);
                    set_player_friction_x(player, FRICTION);
                    set_player_direction(player, 0, -1);
                }
            }
        }
        else
        {
            if (get_player_y(player) <= get_player_y(&players->players[clossest_player_id]) + get_player_h(&players->players[clossest_player_id]))
            {

                set_player_friction_y(player, 0);
                set_player_velovity_y(player, BOT_SPEED);
                set_player_friction_x(player, FRICTION);
                set_player_direction(player, 0, 1);
            }
            else if (get_player_y(player) + get_player_h(player) >= get_player_y(&players->players[clossest_player_id]))
            {

                set_player_friction_y(player, 0);
                set_player_velovity_y(player, -BOT_SPEED);
                set_player_friction_x(player, FRICTION);
                set_player_direction(player, 0, -1);
            }
        }
    }
    else
    {
        set_player_friction_x(player, FRICTION);
        set_player_friction_y(player, FRICTION);
    }

    // If colide with wall
    for (int i = 0; i < obstacles->count_obstacles; i++)
    {
        if (SDL_HasIntersection(get_player_rectangle(player), obstacles->obstacles[i].rectangle))
        {
            if (get_player_y(player) < get_obstacle_y(&obstacles->obstacles[i]) + get_obstacle_h(&obstacles->obstacles[i]) - 10 && get_player_y(player) + get_player_h(player) > get_obstacle_y(&obstacles->obstacles[i]) + 10)
            {

                if (get_player_x(player) <= get_obstacle_x(&obstacles->obstacles[i]) + get_obstacle_w(&obstacles->obstacles[i]) && get_player_x(player) > get_obstacle_x(&obstacles->obstacles[i]) + (get_obstacle_w(&obstacles->obstacles[i]) / 2))
                {
                    // LEFT collision

                    set_player_friction_y(player, 0);
                    set_player_velovity_y(player, BOT_SPEED);
                    set_player_friction_x(player, FRICTION);
                    set_player_direction(player, 0, 1);
                }
                else if (get_player_x(player) + get_player_w(player) >= get_obstacle_x(&obstacles->obstacles[i]))
                {
                    // RIGHT collision

                    set_player_friction_y(player, 0);
                    set_player_velovity_y(player, -BOT_SPEED);
                    set_player_friction_x(player, FRICTION);
                    set_player_direction(player, 0, -1);
                }
            }
            else
            {
                if (get_player_y(player) <= get_obstacle_y(&obstacles->obstacles[i]) + get_obstacle_h(&obstacles->obstacles[i]) && get_player_y(player) > get_obstacle_y(&obstacles->obstacles[i]) + (get_obstacle_h(&obstacles->obstacles[i]) / 2))
                {

                    // DOWN collision
                    set_player_friction_x(player, 0);
                    set_player_velovity_x(player, -BOT_SPEED);
                    set_player_friction_y(player, FRICTION);
                    set_player_direction(player, -1, 0);
                }
                else if (get_player_y(player) + get_player_h(player) >= get_obstacle_y(&obstacles->obstacles[i]))
                {

                    // UP collision
                    set_player_friction_x(player, 0);
                    set_player_velovity_x(player, BOT_SPEED);
                    set_player_friction_y(player, FRICTION);
                    set_player_direction(player, 1, 0);
                }
            }
        }
    }

    if (get_player_heath(player) > 0 && clossest_player_id != -1)
    {
        spawn_projectil(player, projectils, window, time);
    }
}