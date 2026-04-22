/*
** EPITECH PROJECT, 2026
** game design
** File description:
** expedition 33 X borne d'arcane
*/

#include "game.h"

static void print_help(void)
{
    write(1, "Name: EXPEDITION 33 - ARCADE\n", 33);
    write(1, "USAGE\n", 6);
    write(1, "    ./my_hunter\n\n", 17);
    write(1, "DESCRIPTION\n", 12);
    write(1, "    My Hunter is a duck hunt game where"
        "you must shoot ducks.\n", 62);
    write(1, "    Ducks appear on screen and move"
        "from one side to another.\n", 62);
    write(1, "    Click on them to shoot them down!\n\n", 39);
    write(1, "CONTROLS\n", 9);
    write(1, "    Flèches / WASD : Déplacer Gustave\n", 28);
    write(1, "ESPACE         : Attaquer (coup d'épée)\n", 43);
    write(1, "SHIFT              : Lancer sort de peinture\n", 42);
    write(1, "    ESC: Quit the game\n", 24);
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

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;

    if (check_args(argc, argv))
        return 0;
    Game* game = game_create();
    if (!game) {
        fprintf(stderr, "Erreur: impossible de créer le jeu\n");
        return 1;
    }

    game_run(game);
    game_destroy(game);

    return 0;
}
