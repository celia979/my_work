/*
** EPITECH PROJECT, 2025
** my_radar
** File description:
** circle handler
*/

#include "./my.h"

void get_circle_center(sfCircleShape *circle, float *x, float *y)
{
    float radius = sfCircleShape_getRadius(circle);
    sfVector2f pos = sfCircleShape_getPosition(circle);

    *x = pos.x + radius;
    *y = pos.y + radius;
}

int check_circle_distance(circle_pair_t *pair)
{
    float distance_squared = pow((pair->x1 - pair->x2), 2) +
        pow((pair->y1 - pair->y2), 2);
    float radius_sum_squared = pow((pair->r1 + pair->r2), 2);

    if (distance_squared <= radius_sum_squared)
        return 1;
    return 0;
}

void set_circle_colors(sfCircleShape *c1, sfCircleShape *c2, int hit)
{
    if (hit) {
        sfCircleShape_setFillColor(c1, sfWhite);
        sfCircleShape_setFillColor(c2, sfWhite);
        return;
    }
    sfCircleShape_setFillColor(c1, sfTransparent);
}
