/*
** EPITECH PROJECT, 2025
** csfml
** File description:
** enemy manager
*/

#include "struct.h"
#include <stdlib.h>
#include <unistd.h>

static int check_error_manager(const char *filepath, enemy_manager_t *manager)
{
    if (!manager)
        return 0;
    manager->shared_texture = sfTexture_createFromFile(filepath, NULL);
    if (!manager->shared_texture) {
        free(manager);
        return 0;
    }
    return 0;
}

enemy_manager_t *init_enemy_manager(int count, const char *filepath)
{
    enemy_manager_t *manager = malloc(sizeof(enemy_manager_t));
    int i;

    check_error_manager(filepath, manager);
    manager->enemies = malloc(sizeof(sprite_data_t *) * count);
    if (!manager->enemies) {
        sfTexture_destroy(manager->shared_texture);
        free(manager);
        return NULL;
    }
    manager->count = count;
    for (i = 0; i < count; i++) {
        manager->enemies[i] = create_enemy(manager->shared_texture);
        if (!manager->enemies[i])
            return NULL;
        manager->enemies[i]->position.x = -150 - (i * 200);
        sfSprite_setPosition(manager->enemies[i]->sprite,
            manager->enemies[i]->position);
    }
    return manager;
}

void update_enemies(enemy_manager_t *manager)
{
    int i;

    for (i = 0; i < manager->count; i++) {
        if (manager->enemies[i]->is_alive) {
            animate_sprite(manager->enemies[i], 0.15f);
            move_sprite(manager->enemies[i]);
        } else {
            respawn_enemy(manager->enemies[i]);
        }
    }
}

void draw_enemies(enemy_manager_t *manager, sfRenderWindow *window)
{
    int i;

    for (i = 0; i < manager->count; i++) {
        if (manager->enemies[i]->is_alive) {
            sfRenderWindow_drawSprite(window, manager->enemies[i]->sprite,
                NULL);
        }
    }
}

void manage_enemy(enemy_manager_t *manager, int i)
{
    if (manager->enemies[i]->sprite)
        sfSprite_destroy(manager->enemies[i]->sprite);
    if (manager->enemies[i]->anim_clock)
        sfClock_destroy(manager->enemies[i]->anim_clock);
    if (manager->enemies[i]->move_clock)
        sfClock_destroy(manager->enemies[i]->move_clock);
    if (manager->enemies[i]->respawn_clock)
        sfClock_destroy(manager->enemies[i]->respawn_clock);
    free(manager->enemies[i]);
}

void destroy_enemy_manager(enemy_manager_t *manager)
{
    int i;

    if (!manager)
        return;
    for (i = 0; i < manager->count; i++) {
        if (manager->enemies[i]) {
            manage_enemy(manager, i);
        }
    }
    free(manager->enemies);
    if (manager->shared_texture)
        sfTexture_destroy(manager->shared_texture);
    free(manager);
}
