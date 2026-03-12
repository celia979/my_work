/*
** EPITECH PROJECT, 2025
** csfml
** File description:
** animation header
*/

#include <stdlib.h>
#include <unistd.h>

#ifndef ANIMATION_H
    #define ANIMATION_H

    #include <SFML/Graphics.h>

typedef struct sprite_data_s {
    sfSprite *sprite;
    sfTexture *texture;
    sfIntRect rect;
    sfVector2f position;
    sfClock *anim_clock;
    sfClock *move_clock;
    sfClock *respawn_clock;
    float speed;
    int is_alive;
} sprite_data_t;

typedef struct crosshair_s {
    sfCircleShape *shape;
    sfVector2f position;
    float radius;
} crosshair_t;

typedef struct enemy_manager_s {
    sprite_data_t **enemies;
    int count;
    sfTexture *shared_texture;
} enemy_manager_t;

crosshair_t *init_crosshair(float radius);
enemy_manager_t *init_enemy_manager(int count, const char *filepath);
sprite_data_t *create_enemy(sfTexture *texture);

float random_speed(void);
float random_y_position(void);
void animate_sprite(sprite_data_t *data, float delay);
void move_sprite(sprite_data_t *data);
void update_crosshair(crosshair_t *crosshair, sfRenderWindow *window);
int check_collision(sprite_data_t *sprite, crosshair_t *crosshair);
void handle_click_multiple(enemy_manager_t *manager, crosshair_t *crosshair,
    sfEvent event);
void destroy_crosshair(crosshair_t *crosshair);
void respawn_enemy(sprite_data_t *enemy);
void destroy_enemy_manager(enemy_manager_t *manager);
void respawn_enemy(sprite_data_t *enemy);
void update_enemies(enemy_manager_t *manager);
void draw_enemies(enemy_manager_t *manager, sfRenderWindow *window);
void display_count(sprite_data_t *enemy);

#endif /* ANIMATION_H */
