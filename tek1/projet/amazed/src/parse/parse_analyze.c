/*
** EPITECH PROJECT, 2026
** A-Maze-d
** File description:
** Checker for parsing
*/

#include "amazed.h"

void skip_word(char *line, int *i)
{
    while (line[*i] && line[*i] != ' ' && line[*i] != '\t' &&
        line[*i] != '\n' && line[*i] != '#')
        (*i)++;
}

/**
 * @brief Comme son nom l'indique, je compte le nombre de données car :
 * Pour les liens c'est X-X
 * Pour les rooms c'est X X X
 * Donc plus simple pour les différenciers.
 *
 * @param line
 * @return int
 */
int count_nb_of_values_in_line(char *line)
{
    int counter = 0;
    int i = 0;

    while (line[i]) {
        while (line[i] &&
            (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
            i++;
        if (line[i] && line[i] != '#') {
            counter++;
            skip_word(line, &i);
        }
        if (line[i] == '#')
            break;
    }
    return counter;
}

/**
 * @brief Là je regarde en fonction des flags ##start et ##end
 * et pour les autres, s'il y a une donnée et un "-",
 * j'appelle add_link pour stocker les salles liées.
 * s'il y a 3 données,
 * j'appelle add_room pour stocker le nom de la salle et ses postitions
 *
 * @param maze
 * @param line
 * @return int
 */
int sort_elements(maze_t *maze, char *line)
{
    int nb_of_values = count_nb_of_values_in_line(line);
    int tiret_flag = 0;

    for (int i = 0; line[i] && line[i] != '#'; i++)
        if (line[i] == '-')
            tiret_flag = 1;
    if (nb_of_values == 1 && tiret_flag) {
        add_link(maze, line);
        return 0;
    }
    if (nb_of_values == 3) {
        add_room(maze, line);
        return 0;
    }
    if (maze->nb_robots == 0 && nb_of_values == 1 &&
        line[0] >= '0' && line[0] <= '9') {
        maze->nb_robots = my_getnbr(line);
        return 0;
    }
    return 84;
}

/**
 * @brief Je mets juste le flag pour start et end
 * et ensuite j'appelle sort_elements.
 * J'ignore aussi les # seul comme c'est des commentaires.
 *
 * @param maze
 * @param line
 * @return int
 */
int analyze_line(maze_t *maze, char *line)
{
    if (line[0] == '\n' || (line[0] == '#' && line[1] != '#'))
        return 0;
    if (my_strcmp(line, "##start\n") == 0) {
        if (maze->parse_flag == 1 || maze->start != NULL)
            return 84;
        maze->parse_flag = 1;
        return 0;
    }
    if (my_strcmp(line, "##end\n") == 0) {
        if (maze->parse_flag == 2 || maze->end != NULL)
            return 84;
        maze->parse_flag = 2;
        return 0;
    }
    return sort_elements(maze, line);
}
