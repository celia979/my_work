/*
** EPITECH PROJECT, 2026
** A-Maze-d
** File description:
** Select optimal paths for N robots
*/

#include "amazed.h"

//longeur du chemin
int get_path_len(paths_t *paths, int i)
{
    int len = 0;

    while (paths->paths[i][len] != -1)
        len++;
    return len;
}

//Calcule combien de tours sont nécessaires si on utilise k chemins pour faire passer nb_robots robots
int estimate_turns(paths_t *paths, int k, int nb_robots)
{
    int turns = 0;
    int robots_left = nb_robots;
    int steps = 0;
    int on_path = 0;
    int t = 0;

    for (int i = 0; i < k && robots_left > 0; i++) {
        steps = get_path_len(paths, i) - 1;
        on_path = (robots_left + (k - i) - 1) / (k - i);
        t = steps + on_path - 1;
        if (t > turns)
            turns = t;
        robots_left -= on_path;
    }
    return turns;
}

//Teste tous les nombres de chemins possibles, retourne le plus best
int select_best_nb_paths(paths_t *paths, int nb_robots)
{
    int best_k = 1;
    int best_turns = estimate_turns(paths, 1, nb_robots);
    int t = 0;
    int k = 0;

    for (k = 2; k <= paths->nb_paths; k++) {
        t = estimate_turns(paths, k, nb_robots);
        if (t < best_turns) {
            best_turns = t;
            best_k = k;
        }
    }
    return best_k;
}
