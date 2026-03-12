/*
** EPITECH PROJECT, 2025
** csfml
** File description:
** animation functions
*/

#include "struct.h"
#include <stdlib.h>

crosshair_t *init_crosshair(float radius)
{
    crosshair_t *crosshair = malloc(sizeof(crosshair_t));

    if (!crosshair)
        return NULL;
    crosshair->shape = sfCircleShape_create();
    if (!crosshair->shape) {
        free(crosshair);
        return NULL;
    }
    crosshair->radius = radius;
    sfCircleShape_setRadius(crosshair->shape, radius);
    sfCircleShape_setFillColor(crosshair->shape, sfTransparent);
    sfCircleShape_setOutlineThickness(crosshair->shape, 1);
    sfCircleShape_setOutlineColor(crosshair->shape, sfRed);
    sfCircleShape_setOrigin(crosshair->shape, (sfVector2f){radius, radius});
    return crosshair;
}

void animate_sprite(sprite_data_t *data, float delay)
{
    sfTime time = sfClock_getElapsedTime(data->anim_clock);
    float seconds = time.microseconds / 1000000.0f;

    if (seconds > delay) {
        data->rect.left += 110;
        if (data->rect.left >= 330)
            data->rect.left = 0;
        sfSprite_setTextureRect(data->sprite, data->rect);
        sfClock_restart(data->anim_clock);
    }
}

void move_sprite(sprite_data_t *data)
{
    sfTime time = sfClock_getElapsedTime(data->move_clock);
    float deltaTime = time.microseconds / 1000000.0f;

    if (!data->is_alive)
        return;
    data->position.x += data->speed * deltaTime;
    if (data->position.x > 850)
        data->position.x = -150;
    sfSprite_setPosition(data->sprite, data->position);
    sfClock_restart(data->move_clock);
}

void update_crosshair(crosshair_t *crosshair, sfRenderWindow *window)
{
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(window);

    crosshair->position.x = mouse_pos.x;
    crosshair->position.y = mouse_pos.y;
    sfCircleShape_setPosition(crosshair->shape, crosshair->position);
}
