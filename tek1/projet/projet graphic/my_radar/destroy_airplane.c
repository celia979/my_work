/*
** EPITECH PROJECT, 2025
** my_radar
** File description:
** airplane manager
*/

#include "./my.h"

void destroy_reached_airplane(game_data_t *game, int i)
{
    sfSprite_destroy(game->airplane_manager->airplanes[i]->sprite);
    sfClock_destroy(game->airplane_manager->airplanes[i]->move_clock);
    free(game->airplane_manager->airplanes[i]);
    game->airplane_manager->airplanes[i] = NULL;
}

static int has_airplane_reached_target(game_data_t *game, int i)
{
    if (has_reached_destination(
            game->airplane_manager->airplanes[i],
            &game->airplane_manager->airplanes[i]->target))
        return 1;
    return 0;
}

int should_destroy_airplane(game_data_t *game, int i)
{
    if (!game->airplane_manager->airplanes[i]->active)
        return 1;
    if (has_airplane_reached_target(game, i))
        return 1;
    return 0;
}

void destroy_airplane(sp_data_t *airplane)
{
    if (!airplane)
        return;
    sfSprite_destroy(airplane->sprite);
    sfClock_destroy(airplane->move_clock);
    free(airplane);
}

void destroy_airplane_manager(manager_circle_airplane_t *manager)
{
    int i = 0;

    if (!manager)
        return;
    for (i = 0; i < manager->count; i++)
        destroy_airplane(manager->airplanes[i]);
    free(manager->airplanes);
    free(manager);
}

void destroy_towers(tower_t *towers, int count)
{
    int i = 0;

    if (!towers)
        return;
    for (i = 0; i < count; i++)
        sfCircleShape_destroy(towers[i].zone);
    free(towers);
}
