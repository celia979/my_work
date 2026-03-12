/*
** EPITECH PROJECT, 2025
** my_radar
** File description:
** airplane spawn (fixed instant spawn for delay 0)
*/

#include "./my.h"

static int find_empty_slot(manager_circle_airplane_t *manager)
{
    int i = 0;

    for (i = 0; i < manager->count; i++) {
        if (!manager->airplanes[i])
            return i;
    }
    return -1;
}

int should_spawn_airplane(game_data_t *game, int index)
{
    float elapsed_time = 0.0f;
    float delay_seconds = 0.0f;

    delay_seconds = (float)game->script->airplanes[index].delay / 10.0f;
    if (delay_seconds <= 0.0f)
        return 1;
    elapsed_time = sfTime_asSeconds(sfClock_getElapsedTime(game->spawn_clock));
    if (elapsed_time >= delay_seconds)
        return 1;
    return 0;
}

int can_spawn_airplane(game_data_t *game)
{
    if (game->next_airplane_index >= game->script->airplane_count)
        return 0;
    if (!should_spawn_airplane(game, game->next_airplane_index))
        return 0;
    return 1;
}

void spawn_next_airplane(game_data_t *game)
{
    int slot = 0;

    if (!can_spawn_airplane(game))
        return;
    slot = find_empty_slot(game->airplane_manager);
    if (slot == -1)
        return;
    add_airplane_to_manager(game, slot);
}

void handle_airplane_spawn(game_data_t *game)
{
    spawn_next_airplane(game);
}
