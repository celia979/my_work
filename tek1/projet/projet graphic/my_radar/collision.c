/*
** EPITECH PROJECT, 2025
** my_radar
** File description:
** collision handler
*/

#include "./my.h"

int is_intersecting_circles(sfCircleShape *circle, sfCircleShape *circle2)
{
    circle_pair_t pair;
    float r1 = sfCircleShape_getRadius(circle);
    float r2 = sfCircleShape_getRadius(circle2);
    int collision = 0;

    get_circle_center(circle, &pair.x1, &pair.y1);
    get_circle_center(circle2, &pair.x2, &pair.y2);
    pair.r1 = r1;
    pair.r2 = r2;
    collision = check_circle_distance(&pair);
    set_circle_colors(circle, circle2, collision);
    return collision;
}

static void create_rect_from_airplane(sp_data_t *airplane,
    sfFloatRect *rect)
{
    rect->left = airplane->position.x;
    rect->top = airplane->position.y;
    rect->width = 20;
    rect->height = 20;
}

static int check_collision_pair(sp_data_t *a1, sp_data_t *a2)
{
    sfFloatRect rect1;
    sfFloatRect rect2;

    create_rect_from_airplane(a1, &rect1);
    create_rect_from_airplane(a2, &rect2);
    if (sfFloatRect_intersects(&rect1, &rect2, NULL))
        return 1;
    return 0;
}

static int should_destroy_collision(sp_data_t *a1, sp_data_t *a2,
    tower_t *towers, int tower_count)
{
    if (!a1 || !a2 || !a1->active || !a2->active)
        return 0;
    if (!check_collision_pair(a1, a2))
        return 0;
    if (are_both_in_safe_zone(a1, a2, towers, tower_count))
        return 0;
    a1->active = 0;
    a2->active = 0;
    return 1;
}

static int process_airplane_pair(collision_context_t *ctx)
{
    if (!ctx->manager->airplanes[ctx->j])
        return 0;
    if (!ctx->manager->airplanes[ctx->j]->active)
        return 0;
    return should_destroy_collision(ctx->manager->airplanes[ctx->i],
        ctx->manager->airplanes[ctx->j], ctx->towers, ctx->tower_count);
}

static int check_collision_with_others(manager_circle_airplane_t *manager,
    int i, tower_t *towers, int tower_count)
{
    collision_context_t ctx;
    int collision_detected = 0;

    ctx.manager = manager;
    ctx.i = i;
    ctx.towers = towers;
    ctx.tower_count = tower_count;
    for (ctx.j = i + 1; ctx.j < manager->count; ctx.j++) {
        if (process_airplane_pair(&ctx))
            collision_detected = 1;
    }
    return collision_detected;
}

int check_airplane_collisions(manager_circle_airplane_t *manager,
    tower_t *towers, int tower_count)
{
    int i = 0;
    int collision_detected = 0;

    for (i = 0; i < manager->count; i++) {
        if (!manager->airplanes[i] || !manager->airplanes[i]->active)
            continue;
        if (check_collision_with_others(manager, i, towers, tower_count))
            collision_detected = 1;
    }
    return collision_detected;
}
