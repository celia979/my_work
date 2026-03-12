/*
** EPITECH PROJECT, 2026
** amazed.h
** File description:
** Include of Project
*/

#include "my.h"

#ifndef AMAZED
    #define AMAZED

typedef struct room_s {
    char *name;
    int x_coord;
    int y_coord;
} room_t;

typedef struct link_s {
    char *first_room;
    char *second_room;
} link_t;

typedef struct maze_s {
    int parse_flag;
    int nb_robots;
    char *start;
    char *end;
    room_t **rooms;
    link_t **links;
} maze_t;

typedef struct paths_s {
    int **paths;
    int nb_paths;
} paths_t;

typedef struct move_info_s {
    int n;
    int m;
    int length;
    paths_t *paths;
    int *occupied;
    int nb_robots;
} move_info_t;

typedef struct bfs_s {
    int *visited;
    int *queue;
    int *prev;
    int *blocked;
    int n;
    int back;
} bfs_t;

typedef struct bfs_ctx_s {
    int *prev;
    int *blocked;
    int n;
} bfs_ctx_t;

typedef struct robot_s {
    int path;
    int position;
    int end;
    int moved;
} robot_t;

robot_t *assign_paths(int nb_robots, int best_k);
int all_done(robot_t *robots, int nb_robots);
void simulate_turn(robot_t *robots, int best_k, maze_t *maze, paths_t *paths);

int find_room_index(maze_t *maze, char *name);
int count_rooms(maze_t *maze);
int bfs_find_path(maze_t *maze, int *prev, int *blocked, int n);
int *rebuild_path(maze_t *maze, int *prev, int n, int *path_len);
paths_t *find_all_paths(maze_t *maze);
int get_path_len(paths_t *paths, int i);
int select_best_nb_paths(paths_t *paths, int nb_robots);
void free_paths(paths_t *paths);

int analyze_line(maze_t *maze, char *line);
void add_room(maze_t *maze, char *line);
void add_link(maze_t *maze, char *line);
maze_t *parser_maze(void);

void display_maze_info(maze_t *maze);

void free_maze(maze_t *maze);

#endif /* AMAZED */
