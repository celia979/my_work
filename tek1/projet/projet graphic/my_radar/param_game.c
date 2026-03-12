/*
** EPITECH PROJECT, 2025
** my_radar
** File description:
** param of the game
*/

#include "./my.h"

static int load_background_texture(sfTexture **texture, sfSprite **sprite)
{
    *texture = sfTexture_createFromFile("./background.png", NULL);
    if (!(*texture))
        return 84;
    *sprite = sfSprite_create();
    if (!(*sprite)) {
        sfTexture_destroy(*texture);
        return 84;
    }
    return 0;
}

int draw_background(sfRenderWindow *window)
{
    sfTexture *background_texture = NULL;
    sfSprite *background_sprite = NULL;

    if (load_background_texture(&background_texture, &background_sprite) == 84)
        return 0;
    sfSprite_setTexture(background_sprite, background_texture, sfTrue);
    sfRenderWindow_drawSprite(window, background_sprite, NULL);
    sfSprite_destroy(background_sprite);
    sfTexture_destroy(background_texture);
    return 0;
}

static int validate_game_setup(game_data_t *game)
{
    if (!game->towers)
        return 84;
    if (!game->airplane_manager)
        return 84;
    if (!game->spawn_clock)
        return 84;
    return 0;
}

int setup_game(game_data_t *game, script_data_t *script)
{
    game->script = script;
    game->towers = create_towers_from_script(script);
    game->tower_count = script->tower_count;
    game->airplane_manager = init_airplane_manager(script->airplane_count);
    game->spawn_clock = sfClock_create();
    game->next_airplane_index = 0;
    if (validate_game_setup(game) == 84) {
        write(1, "Error: setup game\n", 20);
        return 84;
    }
    return 0;
}

void cleanup_game(game_data_t *game)
{
    destroy_airplane_manager(game->airplane_manager);
    destroy_towers(game->towers, game->tower_count);
    sfClock_destroy(game->spawn_clock);
    sfRenderWindow_destroy(game->window);
}

void draw_tower_sprite(sfRenderWindow *window, tower_t *tower)
{
    sfTexture *texture = NULL;
    sfSprite *sprite = NULL;

    if (load_tower_texture(&texture, &sprite) == 0) {
        sfSprite_setTexture(sprite, texture, sfTrue);
        sfSprite_setPosition(sprite, tower->position);
        sfRenderWindow_drawSprite(window, sprite, NULL);
    }
    if (sprite)
        sfSprite_destroy(sprite);
    if (texture)
        sfTexture_destroy(texture);
}

void destroy_script_data(script_data_t *script)
{
    if (!script)
        return;
    if (script->airplanes)
        free(script->airplanes);
    if (script->towers)
        free(script->towers);
    free(script);
}
