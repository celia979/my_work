/*
** EPITECH PROJECT, 2026
** A-Maze-d
** File description:
** Base of parsing
*/

#include "amazed.h"

void initialize_maze(maze_t *maze)
{
    maze->parse_flag = 0;
    maze->nb_robots = 0;
    maze->start = NULL;
    maze->end = NULL;
    maze->rooms = NULL;
    maze->links = NULL;
}

/**
 * @brief Ici je prends la ligne et je l'analyse
 * pour pouvoir savoir avec analyze_line où il faut stocker la donnée
 *
 * @return maze_t*
 */
maze_t *parser_maze(void)
{
    maze_t *maze = malloc(sizeof(maze_t));
    size_t size = 0;
    char *line = NULL;

    if (!maze)
        return NULL;
    initialize_maze(maze);
    while (getline(&line, &size, stdin) != -1) {
        if (line[0] == '\n')
            break;
        if (analyze_line(maze, line) == 84)
            break;
    }
    free(line);
    return maze;
}
