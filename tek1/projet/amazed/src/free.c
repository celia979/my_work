/*
** EPITECH PROJECT, 2026
** A-Maze-d
** File description:
** Free fucntions for project
*/

#include "amazed.h"

/**
 * @brief On free tout simplement la structure car attention aux valgrinds.
 *
 * @param maze
 */
void free_maze(maze_t *maze)
{
    if (!maze)
        return;
    for (int i = 0; maze->rooms && maze->rooms[i]; i++) {
        free(maze->rooms[i]->name);
        free(maze->rooms[i]);
    }
    if (maze->rooms)
        free(maze->rooms);
    for (int i = 0; maze->links && maze->links[i]; i++) {
        free(maze->links[i]->first_room);
        free(maze->links[i]->second_room);
        free(maze->links[i]);
    }
    if (maze->links)
        free(maze->links);
    free(maze);
}

void free_paths(paths_t *paths)
{
    if (!paths)
        return;
    for (int i = 0; i < paths->nb_paths; i++)
        free(paths->paths[i]);
    free(paths->paths);
    free(paths);
}
