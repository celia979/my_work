/*
** EPITECH PROJECT, 2025
** my_radar
** File description:
** airplane manager
*/

#include "./my.h"

sp_data_t *create_airplane(airplane_config_t *config)
{
    sp_data_t *airplane = malloc(sizeof(sp_data_t));

    if (!airplane)
        return NULL;
    airplane->position = config->start;
    airplane->target = config->end;
    airplane->speed = config->speed;
    airplane->active = 1;
    airplane->delay = config->delay;
    airplane->id = config->id;
    set_airplane_texture(airplane);
    airplane->move_clock = sfClock_create();
    return airplane;
}

static float calculate_distance(sp_data_t *airplane, sfVector2f *target)
{
    float dx = target->x - airplane->position.x;
    float dy = target->y - airplane->position.y;
    float distance = sqrt(dx * dx + dy * dy);

    return distance;
}

static void set_direction_to_zero(sfVector2f *direction)
{
    direction->x = 0.0f;
    direction->y = 0.0f;
}

static void calculate_direction(sp_data_t *airplane, sfVector2f *target,
    sfVector2f *direction, float delta_time)
{
    float dx = target->x - airplane->position.x;
    float dy = target->y - airplane->position.y;
    float distance = calculate_distance(airplane, target);

    if (distance < 1.0f) {
        set_direction_to_zero(direction);
        return;
    }
    direction->x = (dx / distance) * airplane->speed * delta_time;
    direction->y = (dy / distance) * airplane->speed * delta_time;
}

void move_airplane(sp_data_t *airplane, sfVector2f *target)
{
    float delta_time = 0.0f;
    sfVector2f direction;

    delta_time = sfTime_asSeconds(sfClock_restart(airplane->move_clock));
    calculate_direction(airplane, target, &direction, delta_time);
    airplane->position.x += direction.x;
    airplane->position.y += direction.y;
    sfSprite_setPosition(airplane->sprite, airplane->position);
}

int has_reached_destination(sp_data_t *airplane, sfVector2f *target)
{
    float distance = calculate_distance(airplane, target);

    if (distance < 10.0f)
        return 1;
    return 0;
}

static int allocate_airplane_array(manager_circle_airplane_t *manager,
    int count)
{
    manager->airplanes = malloc(sizeof(sp_data_t *) * count);
    if (!manager->airplanes) {
        free(manager);
        return 84;
    }
    return 0;
}

manager_circle_airplane_t *init_airplane_manager(int count)
{
    manager_circle_airplane_t *manager = NULL;
    int i = 0;

    manager = malloc(sizeof(manager_circle_airplane_t));
    if (!manager)
        return NULL;
    if (allocate_airplane_array(manager, count) == 84)
        return NULL;
    manager->count = count;
    for (i = 0; i < count; i++)
        manager->airplanes[i] = NULL;
    return manager;
}
