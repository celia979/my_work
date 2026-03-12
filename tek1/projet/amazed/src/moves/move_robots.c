/*
** EPITECH PROJECT, 2026
** A-maze-d
** File description:
** move_robots.c
*/

#include "amazed.h"

void mark_occupied_room(maze_t *maze, robot_t *robots,
    paths_t *paths, int *occupied)
{
    int room_flag = 0;

    for (int i = 0; i < count_rooms(maze); i++)
        occupied[i] = 0;
    for (int j = 0; j < maze->nb_robots; j++) {
        if (robots[j].end == 0) {
            room_flag = paths->paths[robots[j].path][robots[j].position];
            occupied[room_flag] = 1;
        }
    }
}

void handle_robots_move(robot_t *robots, move_info_t *info)
{
    int cible = 0;

    for (int i = 0; i < info->nb_robots; i++) {
        if (robots[i].path != info->n || robots[i].position != info->m)
            continue;
        cible = info->paths->paths[info->n][info->m + 1];
        if (info->occupied[cible] == 0 || (info->m + 1) == info->length - 1) {
            info->occupied[info->paths->paths[info->n][info->m]] = 0;
            info->occupied[cible] = 1;
            robots[i].position++;
            robots[i].end = (robots[i].position == info->length - 1);
            robots[i].moved = 1;
        }
    }
}

void logical_robots_move(robot_t *robots, int best_k,
    maze_t *laby, paths_t *paths)
{
    int occupied[count_rooms(laby)];
    move_info_t info;

    mark_occupied_room(laby, robots, paths, occupied);
    for (int n = 0; n < best_k; n++) {
        info.n = n;
        info.length = get_path_len(paths, n);
        info.paths = paths;
        info.occupied = occupied;
        info.nb_robots = laby->nb_robots;
        for (int m = info.length - 2; m >= 0; m--) {
            info.m = m;
            handle_robots_move(robots, &info);
        }
    }
}

void simulate_turn(robot_t *robots, int best_k,
    maze_t *maze, paths_t *paths)
{
    int first_move = 1;
    int idx = 0;
    char *room_name = NULL;

    logical_robots_move(robots, best_k, maze, paths);
    for (int i = 0; i < maze->nb_robots; i++) {
        if (robots[i].moved == 0)
            continue;
        if (first_move == 0)
            my_putchar(' ');
        idx = paths->paths[robots[i].path][robots[i].position];
        room_name = maze->rooms[idx]->name;
        mini_printf("P%d-%s", i + 1, room_name);
        first_move = 0;
        robots[i].moved = 0;
    }
    my_putchar('\n');
}
