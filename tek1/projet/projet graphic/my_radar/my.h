/*
** EPITECH PROJECT, 2025
** my_radar
** File description:
** my.h
*/

#ifndef MY_H
    #define MY_H

    #include <SFML/Graphics.h>
    #include <SFML/Audio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <math.h>
    #include <stdio.h>
    #include <time.h>

typedef struct tower_s
{
    sfVector2f position;
    float radius;
    sfCircleShape *zone;
} tower_t;

typedef struct sprite_data_s
{
    sfSprite *sprite;
    sfTexture *texture;
    sfIntRect rect;
    sfVector2f position;
    sfClock *move_clock;
    float speed;
    sfVector2f target;
    int active;
    int delay;
    int id;
} sp_data_t;

typedef struct manager_circle_airplane_s
{
    sp_data_t **airplanes;
    int count;
    sfTexture *shared_texture;
} manager_circle_airplane_t;

typedef struct airplane_data_s
{
    float start_x;
    float start_y;
    float end_x;
    float end_y;
    int delay;
    int id;
} plane_data_t;

typedef struct tower_data_s
{
    float x;
    float y;
    float radius;
    int id;
} tower_data_t;

typedef struct script_data_s
{
    plane_data_t *airplanes;
    tower_data_t *towers;
    int airplane_count;
    int tower_count;
} script_data_t;

typedef struct game_data_s
{
    sfRenderWindow *window;
    manager_circle_airplane_t *airplane_manager;
    tower_t *towers;
    int tower_count;
    sfClock *spawn_clock;
    script_data_t *script;
    int next_airplane_index;
} game_data_t;

typedef struct collision_context_s
{
    manager_circle_airplane_t *manager;
    int i;
    int j;
    tower_t *towers;
    int tower_count;
} collision_context_t;

typedef struct circle_pair_s
{
    float x1;
    float y1;
    float x2;
    float y2;
    float r1;
    float r2;
} circle_pair_t;

typedef struct airplane_config_s
{
    sfVector2f start;
    sfVector2f end;
    float speed;
    int delay;
    int id;
} airplane_config_t;

//tower
int create_tower(sfRenderWindow *window);
float calculate_tower_distance(sfVector2f *pos, tower_t *tower);
float random_y_position(void);
float random_x_position(void);
tower_t *create_towers_from_script(script_data_t *script);
void draw_towers(sfRenderWindow *window, tower_t *towers, int count);

//safe zone
int is_airplane_in_zone(sp_data_t *airplane,
    tower_t *towers, int count);
int are_both_in_safe_zone(sp_data_t *a1, sp_data_t *a2,
    tower_t *towers, int tower_count);

//circle
sfCircleShape *create_circle(sfVector2f *position, float radius);
void get_circle_center(sfCircleShape *circle, float *x, float *y);
int check_circle_distance(circle_pair_t *pair);
void set_circle_colors(sfCircleShape *c1, sfCircleShape *c2, int hit);

//collision
int is_intersecting_circles(sfCircleShape *circle, sfCircleShape *circle2);
int check_airplane_collisions(manager_circle_airplane_t *manager,
    tower_t *towers, int tower_count);

//airplane
sp_data_t *create_airplane(airplane_config_t *config);
manager_circle_airplane_t *init_airplane_manager(int count);
void handle_airplane_spawn(game_data_t *game);
void update_all_airplanes(game_data_t *game);
void draw_all_airplanes(sfRenderWindow *window,
    manager_circle_airplane_t *manager);
void move_airplane(sp_data_t *airplane, sfVector2f *target);
int has_reached_destination(sp_data_t *airplane, sfVector2f *target);
int should_spawn_airplane(game_data_t *game, int index);
int can_spawn_airplane(game_data_t *game);
void spawn_next_airplane(game_data_t *game);
void handle_airplane_spawn(game_data_t *game);
void add_airplane_to_manager(game_data_t *game, int slot);

//destroy
void destroy_airplane_manager(manager_circle_airplane_t *manager);
void destroy_towers(tower_t *towers, int count);
void destroy_reached_airplane(game_data_t *game, int i);
int should_destroy_airplane(game_data_t *game, int i);
void destroy_script_data(script_data_t *script);
void destroy_airplane(sp_data_t *airplane);

//game and setting
void draw_tower_sprite(sfRenderWindow *window, tower_t *tower);
int load_tower_texture(sfTexture **texture, sfSprite **sprite);
int draw_background(sfRenderWindow *window);
int setup_game(game_data_t *game, script_data_t *script);
void cleanup_game(game_data_t *game);
script_data_t *parse_script_file(char const *filepath);
void calculate_texture_scale(sfVector2u *texture_size,
    float *scale_x, float *scale_y);
void apply_texture_to_sprite(sp_data_t *airplane);
void set_airplane_texture(sp_data_t *airplane);
int validate_counts(script_data_t *script);

//parser
int allocate_script_data(script_data_t *script);
int count_lines(char const *filepath, char type);
int read_script_content(char const *filepath, script_data_t *script);
int validate_file(char const *filepath);

//parser utils
void skip_spaces(char *str, int *i);
float parse_float(char *str, int *i);
int parse_int(char *str, int *i);
int parse_airplane_line(char *line, plane_data_t *data);
int parse_tower_line(char *line, tower_data_t *data);

#endif
