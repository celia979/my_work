/*
** EPITECH PROJECT, 2025
** csfml
** File description:
** destroy enemy
*/

#include "struct.h"
#include <stdlib.h>
#include <unistd.h>

int check_collision(sprite_data_t *sprite, crosshair_t *crosshair)
{
    sfFloatRect sprite_bounds;

    if (!sprite->is_alive)
        return 0;
    sprite_bounds = sfSprite_getGlobalBounds(sprite->sprite);
    if (crosshair->position.x >= sprite_bounds.left &&
        crosshair->position.x <= sprite_bounds.left + sprite_bounds.width &&
        crosshair->position.y >= sprite_bounds.top &&
        crosshair->position.y <= sprite_bounds.top + sprite_bounds.height) {
        return 1;
    }
    return 0;
}

void handle_click(sprite_data_t *sprite, crosshair_t *crosshair)
{
    if (sfMouse_isButtonPressed(sfMouseLeft)) {
        if (check_collision(sprite, crosshair)) {
            sprite->is_alive = 0;
            sfClock_restart(sprite->respawn_clock);
        }
    }
}

void condition_click_multiple(enemy_manager_t *manager, crosshair_t *crosshair)
{
    int i;

    for (i = 0; i < manager->count; i++) {
        if (check_collision(manager->enemies[i], crosshair)) {
            manager->enemies[i]->is_alive = 0;
            manager->enemies[i]->position.x = -150;
            sfSprite_setPosition(manager->enemies[i]->sprite,
                manager->enemies[i]->position);
            sfClock_restart(manager->enemies[i]->respawn_clock);
            break;
        }
    }
}

void handle_click_multiple(enemy_manager_t *manager, crosshair_t *crosshair,
    sfEvent event)
{
    if (event.type == sfEvtMouseButtonPressed &&
        event.mouseButton.button == sfMouseLeft) {
        condition_click_multiple(manager, crosshair);
    }
}

void destroy_crosshair(crosshair_t *crosshair)
{
    if (!crosshair)
        return;
    if (crosshair->shape)
        sfCircleShape_destroy(crosshair->shape);
    free(crosshair);
}
