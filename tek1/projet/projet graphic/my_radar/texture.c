/*
** EPITECH PROJECT, 2025
** my_radar
** File description:
** texture
*/

#include "./my.h"

void calculate_texture_scale(sfVector2u *texture_size,
    float *scale_x, float *scale_y)
{
    *scale_x = 20.0f / texture_size->x;
    *scale_y = 20.0f / texture_size->y;
}

void apply_texture_to_sprite(sp_data_t *airplane)
{
    sfVector2u texture_size;
    float scale_x = 0.0f;
    float scale_y = 0.0f;

    texture_size = sfTexture_getSize(airplane->texture);
    calculate_texture_scale(&texture_size, &scale_x, &scale_y);
    sfSprite_setTexture(airplane->sprite, airplane->texture, sfTrue);
    sfSprite_setScale(airplane->sprite, (sfVector2f){scale_x, scale_y});
}

void set_airplane_texture(sp_data_t *airplane)
{
    airplane->sprite = sfSprite_create();
    airplane->texture = sfTexture_createFromFile("./avion.png", NULL);
    if (airplane->texture)
        apply_texture_to_sprite(airplane);
    sfSprite_setPosition(airplane->sprite, airplane->position);
}

int load_tower_texture(sfTexture **texture, sfSprite **sprite)
{
    *texture = sfTexture_createFromFile("./tourdecontrol.png", NULL);
    *sprite = sfSprite_create();
    if (!(*texture) || !(*sprite))
        return 84;
    return 0;
}
