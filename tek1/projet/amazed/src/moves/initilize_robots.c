/*
** EPITECH PROJECT, 2026
** A-maze-d
** File description:
** initilize_robots.c
*/

#include "amazed.h"

robot_t *init_robots(int nb_robots)
{
    robot_t *robot = malloc(sizeof(robot_t) * nb_robots);

    if (robot == NULL)
        return NULL;
    for (int i = 0; i < nb_robots; i++) {
        robot[i].position = 0;
        robot[i].end = 0;
        robot[i].moved = 0;
    }
    return robot;
}

robot_t *assign_paths(int nb_robots, int best_k)
{
    robot_t *robot = init_robots(nb_robots);

    if (robot == NULL)
        return NULL;
    for (int i = 0; i < nb_robots; i++) {
        robot[i].path = i % best_k;
    }
    return robot;
}

int all_done(robot_t *robots, int nb_robots)
{
    for (int i = 0; i < nb_robots; i++) {
        if (robots[i].end == 0)
            return 0;
    }
    return 1;
}
