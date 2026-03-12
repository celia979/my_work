/*
** EPITECH PROJECT, 2026
** A-Maze-d
** File description:
** BFS to find shortest path
*/

#include "amazed.h"

//cherche une salle par son nom, retourne sa position
int find_room_index(maze_t *maze, char *name)
{
    int i = 0;

    for (i = 0; maze->rooms && maze->rooms[i]; i++)
        if (my_strcmp(maze->rooms[i]->name, name) == 0)
            return i;
    return -1;
}

//compte le nombre de salle totale, pour pouvoir allouer le bon nombre
int count_rooms(maze_t *maze)
{
    int count = 0;

    while (maze->rooms && maze->rooms[count])
        count++;
    return count;
}

//initialise 2 tableau, visited = deja aller ?, prev = par quelle salle on est arrivier
static void init_bfs(int *visited, int *prev, int n)
{
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
        prev[i] = -1;
    }
}

//i = tunnel entre 2salles, on retourne le voisin de current (de la salle)
static int get_neighbor(maze_t *maze, int current, int i)
{
    int a = find_room_index(maze, maze->links[i]->first_room);
    int b = find_room_index(maze, maze->links[i]->second_room);

    if (a == current)
        return b;
    if (b == current)
        return a;
    return -1;
}

//neighbor comme visité, mémorise qu'on y est arrivé depuis current dans prev[], et l'ajoute dans la file d'attente queue[]
static void bfs_visit(bfs_t *bfs, int neighbor, int current)
{
    bfs->visited[neighbor] = 1;
    bfs->prev[neighbor] = current;
    bfs->queue[bfs->back] = neighbor;
    bfs->back = bfs->back + 1;
}

//traite la file, regarde les voisin, si la salle est pas bloquer et non visiter on appelle bfs_visite()
static void bfs_expand(bfs_t *bfs, maze_t *maze, int front)
{
    int current = bfs->queue[front];
    int neighbor = 0;

    for (int i = 0; maze->links && maze->links[i]; i++) {
        neighbor = get_neighbor(maze, current, i);
        if (neighbor < 0 || neighbor >= bfs->n)
            continue;
        if (!bfs->visited[neighbor] && !bfs->blocked[neighbor])
            bfs_visit(bfs, neighbor, current);
    }
}

//Tant qu'il y a des salles dans la file, on expand la suivante
static void run_bfs(bfs_t *bfs, maze_t *maze, int start_idx)
{
    int front = 0;

    init_bfs(bfs->visited, bfs->prev, bfs->n);
    bfs->visited[start_idx] = 1;
    bfs->queue[bfs->back] = start_idx;
    bfs->back = bfs->back + 1;
    while (front < bfs->back) {
        bfs_expand(bfs, maze, front);
        front = front + 1;
    }
}

//Alloue les tableaux, remplit la struct bfs_t, lance run_bfs, puis retourne 1 si end a été atteint sinon 0
int bfs_find_path(maze_t *maze, int *prev, int *blocked, int n)
{
    bfs_t bfs;
    int start_idx = find_room_index(maze, maze->start);
    int end_idx = find_room_index(maze, maze->end);

    bfs.visited = malloc(sizeof(int) * n);
    bfs.queue = malloc(sizeof(int) * n);
    bfs.prev = prev;
    bfs.blocked = blocked;
    bfs.n = n;
    bfs.back = 0;
    if (!bfs.visited || !bfs.queue || start_idx == -1 || end_idx == -1) {
        free(bfs.visited);
        free(bfs.queue);
        return 0;
    }
    run_bfs(&bfs, maze, start_idx);
    free(bfs.visited);
    free(bfs.queue);
    return (prev[end_idx] != -1);
}
