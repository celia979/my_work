/*
** EPITECH PROJECT, 2025
** my_radar
** File description:
** airplane logic (fixed timing issue)
*/

#include "./my.h"

static sp_data_t *create_airplane_from_script(game_data_t *game, int index)
{
    plane_data_t *data = &game->script->airplanes[index];
    airplane_config_t config;
    sp_data_t *new_airplane = NULL;

    config.start = (sfVector2f){data->start_x, data->start_y};
    config.end = (sfVector2f){data->end_x, data->end_y};
    config.speed = 100.0f;
    config.delay = data->delay;
    config.id = data->id;
    new_airplane = create_airplane(&config);
    return new_airplane;
}

void add_airplane_to_manager(game_data_t *game, int slot)
{
    sp_data_t *new_airplane = NULL;

    new_airplane = create_airplane_from_script(game, game->next_airplane_index);
    if (!new_airplane)
        return;
    game->airplane_manager->airplanes[slot] = new_airplane;
    game->next_airplane_index++;
}

static void update_single_airplane(game_data_t *game, int i)
{
    move_airplane(game->airplane_manager->airplanes[i],
        &game->airplane_manager->airplanes[i]->target);
    if (should_destroy_airplane(game, i))
        destroy_reached_airplane(game, i);
}

void update_all_airplanes(game_data_t *game)
{
    int i = 0;

    for (i = 0; i < game->airplane_manager->count; i++) {
        if (!game->airplane_manager->airplanes[i])
            continue;
        update_single_airplane(game, i);
    }
}

static void setup_hitbox(sfRectangleShape *hitbox)
{
    sfRectangleShape_setSize(hitbox, (sfVector2f){20, 20});
    sfRectangleShape_setFillColor(hitbox, sfTransparent);
    sfRectangleShape_setOutlineColor(hitbox, sfRed);
    sfRectangleShape_setOutlineThickness(hitbox, 2);
}

static void draw_airplane_sprite(sfRenderWindow *window, sp_data_t *airplane)
{
    if (airplane->sprite)
        sfRenderWindow_drawSprite(window, airplane->sprite, NULL);
}

static void draw_airplane_hitbox(sfRenderWindow *window,
    sfRectangleShape *hitbox, sfVector2f *pos)
{
    sfRectangleShape_setPosition(hitbox, *pos);
    sfRenderWindow_drawRectangleShape(window, hitbox, NULL);
}

static void draw_single_airplane(sfRenderWindow *window,
    sp_data_t *airplane, sfRectangleShape *hitbox)
{
    draw_airplane_sprite(window, airplane);
    draw_airplane_hitbox(window, hitbox, &airplane->position);
}

static int should_draw_airplane(sp_data_t *airplane)
{
    if (!airplane)
        return 0;
    if (!airplane->active)
        return 0;
    return 1;
}

void draw_all_airplanes(sfRenderWindow *window,
    manager_circle_airplane_t *manager)
{
    int i = 0;
    sfRectangleShape *hitbox = sfRectangleShape_create();

    setup_hitbox(hitbox);
    for (i = 0; i < manager->count; i++) {
        if (should_draw_airplane(manager->airplanes[i]))
            draw_single_airplane(window, manager->airplanes[i], hitbox);
    }
    sfRectangleShape_destroy(hitbox);
}
