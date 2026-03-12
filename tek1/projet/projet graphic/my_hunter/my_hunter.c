/*
** EPITECH PROJECT, 2025
** csfml
** File description:
** initiation
*/

#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "struct.h"

static void print_help(void)
{
    write(1, "USAGE\n", 6);
    write(1, "    ./my_hunter\n\n", 17);
    write(1, "DESCRIPTION\n", 12);
    write(1, "    My Hunter is a duck hunt game where"
        "you must shoot ducks.\n", 62);
    write(1, "    Ducks appear on screen and move"
        "from one side to another.\n", 62);
    write(1, "    Click on them to shoot them down!\n\n", 39);
    write(1, "CONTROLS\n", 9);
    write(1, "    Mouse Left Click: Shoot\n", 28);
    write(1, "    ESC: Quit the game\n", 23);
}

void switch_case(sfRenderWindow *window, sfEvent event)
{
    if (event.key.code == sfKeyEscape)
        sfRenderWindow_close(window);
}

int pollevent(sfRenderWindow *window, sfEvent *event,
    enemy_manager_t *manager, crosshair_t *crosshair)
{
    while (sfRenderWindow_pollEvent(window, event)) {
        if (event->type == sfEvtClosed)
            sfRenderWindow_close(window);
        if (event->type == sfEvtKeyPressed)
            switch_case(window, *event);
        handle_click_multiple(manager, crosshair, *event);
    }
    return 0;
}

void handling_back_ground(sfRenderWindow *window)
{
    sfTexture *floor_t = sfTexture_createFromFile("./background1.png", NULL);
    sfSprite *floor_s = sfSprite_create();

    sfSprite_setTexture(floor_s, floor_t, sfTrue);
    sfRenderWindow_drawSprite(window, floor_s, NULL);
}

void game_loop(sfRenderWindow *window, enemy_manager_t *manager,
    sfEvent event)
{
    crosshair_t *crosshair = init_crosshair(30.0f);

    if (!crosshair)
        return;
    sfRenderWindow_setMouseCursorVisible(window, sfFalse);
    while (sfRenderWindow_isOpen(window)) {
        sfRenderWindow_clear(window, sfBlack);
        handling_back_ground(window);
        update_enemies(manager);
        draw_enemies(manager, window);
        update_crosshair(crosshair, window);
        handle_click_multiple(manager, crosshair, event);
        sfRenderWindow_drawCircleShape(window, crosshair->shape, NULL);
        sfRenderWindow_display(window);
        pollevent(window, &event, manager, crosshair);
    }
    destroy_crosshair(crosshair);
}

static int check_args(int ac, char **av)
{
    if (ac == 2) {
        if (av[1][0] == '-' && av[1][1] == 'h' && av[1][2] == '\0') {
            print_help();
            return 1;
        }
    }
    return 0;
}

static int check_error(sfRenderWindow *window)
{
    if (!window)
        return 84;
    return 0;
    sfRenderWindow_setFramerateLimit(window, 60);
}

int main(int ac, char **av)
{
    sfVideoMode mode = {800, 600, 32};
    sfRenderWindow *window;
    enemy_manager_t *manager;
    sfEvent event;

    if (check_args(ac, av))
        return 0;
    srand(time(NULL));
    window = sfRenderWindow_create(mode, "My Hunter",
        sfDefaultStyle, NULL);
    check_error(window);
    manager = init_enemy_manager(5, "spritesheet.png");
    if (!manager) {
        sfRenderWindow_destroy(window);
        return 84;
    }
    game_loop(window, manager, event);
    destroy_enemy_manager(manager);
    sfRenderWindow_destroy(window);
    return 0;
}
