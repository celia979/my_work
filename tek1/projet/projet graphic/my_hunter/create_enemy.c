/*
** EPITECH PROJECT, 2025
** csfml
** File description:
** create enemy
*/

#include "struct.h"
#include <stdlib.h>

float random_speed(void)
{
    return (80.0f + (rand() % 120));
}

float random_y_position(void)
{
    return (50.0f + (rand() % 400));
}

int check_data_error(sfTexture *texture, sprite_data_t *data)
{
    if (!data)
        return 0;
    data->texture = texture;
    data->sprite = sfSprite_create();
    if (!data->sprite) {
        free(data);
        return 0;
    }
    return 0;
}

sprite_data_t *create_enemy(sfTexture *texture)
{
    sprite_data_t *data = malloc(sizeof(sprite_data_t));
    sfIntRect rect = {0, 0, 110, 110};

    check_data_error(texture, data);
    sfSprite_setTexture(data->sprite, data->texture, sfTrue);
    data->rect = rect;
    data->position = (sfVector2f){-150, random_y_position()};
    data->speed = random_speed();
    data->is_alive = 1;
    data->anim_clock = sfClock_create();
    data->move_clock = sfClock_create();
    data->respawn_clock = sfClock_create();
    sfSprite_setPosition(data->sprite, data->position);
    sfSprite_setTextureRect(data->sprite, data->rect);
    return data;
}

void respawn_enemy(sprite_data_t *enemy)
{
    sfTime time = sfClock_getElapsedTime(enemy->respawn_clock);
    float seconds = time.microseconds / 1000000.0f;

    if (!enemy->is_alive && seconds > 3.0f) {
        enemy->is_alive = 1;
        enemy->position.x = -150;
        enemy->position.y = random_y_position();
        enemy->speed = random_speed();
        enemy->rect.left = 0;
        sfSprite_setPosition(enemy->sprite, enemy->position);
        sfSprite_setTextureRect(enemy->sprite, enemy->rect);
        sfClock_restart(enemy->respawn_clock);
        sfClock_restart(enemy->move_clock);
        sfClock_restart(enemy->anim_clock);
    }
}
