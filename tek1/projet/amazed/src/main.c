/*
** EPITECH PROJECT, 2026
** A-Maze-d
** File description:
** Main file of the project
*/

#include "amazed.h"

int second_check_maze_parse(maze_t *maze)
{
    if (maze->rooms == NULL) {
        write(2, "amazed: You didn't define any rooms.\n", 37);
        return 84;
    }
    if (maze->links == NULL) {
        write(2, "amazed: Please define the tubes after the rooms.\n", 49);
        return 84;
    }
    return 0;
}

/**
 * @brief C'est la fonction qui gère les erreurs relevées par le parsing
 * ou les trucs qui manquent dans le fichier en question
 *
 * @param maze
 * @return int
 */
int check_maze_parse(maze_t *maze)
{
    if (!maze)
        return 84;
    if (maze->nb_robots <= 0) {
        write(2, "amazed: Would be funniest with robots, nah ?\n", 45);
        return 84;
    }
    if (maze->start == NULL) {
        write(2, "amazed: You didn't define any start room.\n", 42);
        return 84;
    }
    if (maze->end == NULL) {
        write(2, "amazed: You didn't define any end room.\n", 40);
        return 84;
    }
    if (second_check_maze_parse(maze) == 84)
        return 84;
    return 0;
}

int run_maze(maze_t *maze)
{
    paths_t *paths = find_all_paths(maze);
    robot_t *robots = NULL;
    int best_k = 0;

    if (!paths || paths->nb_paths == 0) {
        write(2, "There is no valid path from start to exit.\n", 43);
        free_paths(paths);
        return 84;
    }
    best_k = select_best_nb_paths(paths, maze->nb_robots);
    display_maze_info(maze);
    write(1, "#moves\n", 7);
    robots = assign_paths(maze->nb_robots, best_k);
    while (all_done(robots, maze->nb_robots) == 0)
        simulate_turn(robots, best_k, maze, paths);
    free_paths(paths);
    free(robots);
    return 0;
}

int main(int argc, char **argv)
{
    maze_t *maze = parser_maze();

    (void)argv;
    if (argc != 1) {
        write(2, "Usage: ./amazed < [file]\n", 25);
        free_maze(maze);
        return 84;
    }
    if (check_maze_parse(maze) == 84) {
        free_maze(maze);
        return 84;
    }
    if (run_maze(maze) == 84) {
        free_maze(maze);
        return 84;
    }
    free_maze(maze);
    return 0;
}
