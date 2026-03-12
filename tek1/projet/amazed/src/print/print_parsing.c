/*
** EPITECH PROJECT, 2026
** A-Maze-d
** File description:
** Print maze before tunnels
*/

#include "amazed.h"

/**
 * @brief Ici c'est pour display les données stockée dans la strucure,
 * je vous laisserez créer une autre fonction
 * pour display les mouvements des robots.
 *
 * @param maze
 */
void display_maze_info(maze_t *maze)
{
    if (!maze)
        return;
    mini_printf("#number_of_robots\n%d\n", maze->nb_robots);
    my_putstr("#rooms\n");
    for (int i = 0; maze->rooms && maze->rooms[i]; i++) {
        if (maze->start && my_strcmp(maze->rooms[i]->name, maze->start) == 0)
            my_putstr("##start\n");
        if (maze->end && my_strcmp(maze->rooms[i]->name, maze->end) == 0)
            my_putstr("##end\n");
        mini_printf("%s %d %d", maze->rooms[i]->name,
            maze->rooms[i]->x_coord, maze->rooms[i]->y_coord);
        my_putchar('\n');
    }
    my_putstr("#tunnels\n");
    for (int i = 0; maze->links && maze->links[i]; i++)
        mini_printf("%s-%s\n",
            maze->links[i]->first_room, maze->links[i]->second_room);
}
