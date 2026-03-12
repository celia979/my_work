/*
** EPITECH PROJECT, 2025
** my_radar
** File description:
** tower manager (fixed positioning)
*/

#include "./my.h"

static void init_tower(tower_t *tower, sfVector2f *pos, float rad)
{
    tower->position = *pos;
    tower->radius = rad;
    tower->zone = sfCircleShape_create();
    sfCircleShape_setRadius(tower->zone, tower->radius);
    sfCircleShape_setPosition(tower->zone,
        (sfVector2f){pos->x - rad, pos->y - rad});
    sfCircleShape_setFillColor(tower->zone, sfTransparent);
    sfCircleShape_setOutlineColor(tower->zone, sfGreen);
    sfCircleShape_setOutlineThickness(tower->zone, 2);
}

tower_t *create_towers_from_script(script_data_t *script)
{
    tower_t *towers = NULL;
    int i = 0;

    towers = malloc(sizeof(tower_t) * script->tower_count);
    if (!towers)
        return NULL;
    for (i = 0; i < script->tower_count; i++) {
        init_tower(&towers[i],
            &(sfVector2f){script->towers[i].x, script->towers[i].y},
            script->towers[i].radius);
    }
    return towers;
}

void draw_towers(sfRenderWindow *window, tower_t *towers, int count)
{
    int i = 0;

    for (i = 0; i < count; i++) {
        sfRenderWindow_drawCircleShape(window, towers[i].zone, NULL);
        draw_tower_sprite(window, &towers[i]);
    }
}

float calculate_tower_distance(sfVector2f *pos, tower_t *tower)
{
    float dx = pos->x - tower->position.x;
    float dy = pos->y - tower->position.y;
    float distance = sqrt(dx * dx + dy * dy);

    return distance;
}

static int is_in_control_zone(sfVector2f *pos, tower_t *towers, int count)
{
    int i = 0;
    float distance = 0.0f;

    for (i = 0; i < count; i++) {
        distance = calculate_tower_distance(pos, &towers[i]);
        if (distance <= towers[i].radius)
            return 1;
    }
    return 0;
}

int is_airplane_in_zone(sp_data_t *airplane,
    tower_t *towers, int count)
{
    if (is_in_control_zone(&airplane->position, towers, count))
        return 1;
    return 0;
}

int are_both_in_safe_zone(sp_data_t *a1, sp_data_t *a2,
    tower_t *towers, int tower_count)
{
    if (is_airplane_in_zone(a1, towers, tower_count))
        return 1;
    if (is_airplane_in_zone(a2, towers, tower_count))
        return 1;
    return 0;
}
