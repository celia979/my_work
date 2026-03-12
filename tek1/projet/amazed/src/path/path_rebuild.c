/*
** EPITECH PROJECT, 2026
** A-Maze-d
** File description:
** Rebuild path from BFS result and store it
*/

#include "amazed.h"

//Retourne tmp dans le bon sens pour avoir start, ..., end. Ajoute un -1 terminal pour savoir où s'arrête le tableau 
static int *fill_path(int *tmp, int len)
{
    int *path = malloc(sizeof(int) * (len + 1));
    int i = 0;

    if (!path)
        return NULL;
    for (i = 0; i < len; i++)
        path[i] = tmp[len - 1 - i];
    path[len] = -1;
    return path;
}

//Remonte le chemin à l'envers depuis end jusqu'à start grâce au tableau prev[]. Remplit tmp[] dans l'ordre inversé : end, ..., start
static int *trace_back(maze_t *maze, int *prev, int n, int *len)
{
    int end_idx = find_room_index(maze, maze->end);
    int *tmp = malloc(sizeof(int) * n);
    int cur = 0;

    if (!tmp || end_idx == -1)
        return NULL;
    for (cur = end_idx; cur != -1; cur = prev[cur]) {
        tmp[*len] = cur;
        *len = *len + 1;
    }
    return tmp;
}

//Retourne le chemin propre sous forme de tableau d'index, (avec trace_back et fill_path)
int *rebuild_path(maze_t *maze, int *prev, int n, int *path_len)
{
    int *tmp = NULL;
    int *path = NULL;
    int len = 0;

    tmp = trace_back(maze, prev, n, &len);
    if (!tmp)
        return NULL;
    path = fill_path(tmp, len);
    *path_len = len;
    free(tmp);
    return path;
}

//Ajoute un chemin dans paths->paths[]. Réalloue le tableau à chaque fois 
static int append_path(paths_t *paths, int *path)
{
    int **new = malloc(sizeof(int *) * (paths->nb_paths + 2));

    if (!new)
        return 84;
    for (int i = 0; i < paths->nb_paths; i++)
        new[i] = paths->paths[i];
    new[paths->nb_paths] = path;
    new[paths->nb_paths + 1] = NULL;
    free(paths->paths);
    paths->paths = new;
    paths->nb_paths = paths->nb_paths + 1;
    return 0;
}

//Marque les salles intermédiaires d'un chemin comme bloquées dans blocked[], garanti que les chemins ne partage aucune salle(!=start-end)
static void block_path_rooms(maze_t *maze, int *path, int *blocked)
{
    int start_idx = find_room_index(maze, maze->start);
    int end_idx = find_room_index(maze, maze->end);

    for (int i = 0; path[i] != -1; i++) {
        if (path[i] != start_idx && path[i] != end_idx)
            blocked[path[i]] = 1;
    }
}

//Alloue et initialise une structure paths_t vide
static paths_t *init_paths(void)
{
    paths_t *paths = malloc(sizeof(paths_t));

    if (!paths)
        return NULL;
    paths->nb_paths = 0;
    paths->paths = malloc(sizeof(int *));
    if (!paths->paths) {
        free(paths);
        return NULL;
    }
    paths->paths[0] = NULL;
    return paths;
}

//reconstruit le chemin, le stocke, bloque ses salles, recommence. S'arrête quand plus aucun chemin n'est trouvable
static void run_all_bfs(maze_t *maze, paths_t *paths, bfs_ctx_t *ctx)
{
    int path_len = 0;
    int *path = NULL;

    while (bfs_find_path(maze, ctx->prev, ctx->blocked, ctx->n)) {
        path = rebuild_path(maze, ctx->prev, ctx->n, &path_len);
        if (!path)
            break;
        if (append_path(paths, path) == 84) {
            free(path);
            break;
        }
        if (path_len <= 2)
            break;
        block_path_rooms(maze, path, ctx->blocked);
    }
}

//Alloue le contexte (bfs_ctx_t), initialise blocked[] à 0, appelle run_all_bfs, retourne tous les chemins trouvé
paths_t *find_all_paths(maze_t *maze)
{
    int n = count_rooms(maze);
    bfs_ctx_t ctx;
    paths_t *paths = init_paths();

    ctx.prev = malloc(sizeof(int) * n);
    ctx.blocked = malloc(sizeof(int) * n);
    ctx.n = n;
    if (!ctx.prev || !ctx.blocked || !paths) {
        free(ctx.prev);
        free(ctx.blocked);
        free_paths(paths);
        return NULL;
    }
    for (int i = 0; i < n; i++)
        ctx.blocked[i] = 0;
    run_all_bfs(maze, paths, &ctx);
    free(ctx.prev);
    free(ctx.blocked);
    return paths;
}
