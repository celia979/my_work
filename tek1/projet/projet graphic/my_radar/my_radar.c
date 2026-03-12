/*
** EPITECH PROJECT, 2025
** csfml
** File description:
** my radar
*/

#include "./my.h"

static void print_help(void)
{
    write(1, "Air traffic simulation panel\n", 29);
    write(1, "USAGE\n", 6);
    write(1, "  ./my_radar [filepath]\n", 24);
    write(1, "DESCRIPTION:\n", 13);
    write(1, "  filepath: path to the radar script file\n", 43);
    write(1, "  My radar is a game where you must guide", 42);
    write(1, " the airplane to their destination.\n", 37);
    write(1, "  Airplanes appear on screen and move", 38);
    write(1, " when they take off.\n", 22);
    write(1, "  Avoid the airplanes colliding with each other", 48);
    write(1, " until they land.\n\n", 19);
    write(1, "USER INTERACTIONS\n", 18);
    write(1, "  ESC: Quit the game\n", 22);
}

static int check_args(int ac, char **av)
{
    if (ac == 2) {
        if (av[1][0] == '-' && av[1][1] == 'h' && av[1][2] == '\0') {
            print_help();
            return 1;
        }
    }
    if (ac != 2) {
        write(1, "Error: invalid number of arguments\n", 36);
        return 84;
    }
    return 0;
}

void switch_case(sfRenderWindow *window, sfEvent event)
{
    if (event.key.code == sfKeyEscape)
        sfRenderWindow_close(window);
}

int pollevent(sfRenderWindow *window, sfEvent *event)
{
    while (sfRenderWindow_pollEvent(window, event)) {
        if (event->type == sfEvtClosed)
            sfRenderWindow_close(window);
        if (event->type == sfEvtKeyPressed)
            switch_case(window, *event);
    }
    return 0;
}

static void render_frame(game_data_t *game)
{
    sfRenderWindow_clear(game->window, sfBlack);
    draw_background(game->window);
    draw_towers(game->window, game->towers, game->tower_count);
    draw_all_airplanes(game->window, game->airplane_manager);
    sfRenderWindow_display(game->window);
}

void game_loop(game_data_t *game)
{
    sfEvent event;

    while (sfRenderWindow_isOpen(game->window)) {
        handle_airplane_spawn(game);
        update_all_airplanes(game);
        check_airplane_collisions(game->airplane_manager,
            game->towers, game->tower_count);
        render_frame(game);
        pollevent(game->window, &event);
    }
}

static script_data_t *load_script(char const *filepath)
{
    script_data_t *script = NULL;

    if (validate_file(filepath) == 84)
        return NULL;
    script = parse_script_file(filepath);
    if (!script)
        write(1, "Error: incorrect script format\n", 32);
    return script;
}

static int create_window(game_data_t *game)
{
    sfVideoMode mode = {1920, 1080, 32};

    game->window = sfRenderWindow_create(mode, "My Radar", sfClose, NULL);
    if (!game->window) {
        write(1, "Error: couldn't open my_radar\n", 32);
        return 84;
    }
    sfRenderWindow_setFramerateLimit(game->window, 60);
    return 0;
}

static int run_game(char const *filepath)
{
    game_data_t game;
    script_data_t *script = load_script(filepath);

    if (!script)
        return 84;
    if (create_window(&game) == 84) {
        destroy_script_data(script);
        return 84;
    }
    if (setup_game(&game, script) == 84) {
        destroy_script_data(script);
        sfRenderWindow_destroy(game.window);
        return 84;
    }
    game_loop(&game);
    cleanup_game(&game);
    destroy_script_data(script);
    return 0;
}

int main(int ac, char **av)
{
    int check_result = check_args(ac, av);

    if (check_result != 0)
        return (check_result == 1) ? 0 : 84;
    srand(time(NULL));
    return run_game(av[1]);
}
