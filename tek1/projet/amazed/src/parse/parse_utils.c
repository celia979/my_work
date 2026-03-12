/*
** EPITECH PROJECT, 2026
** A-Maze-d
** File description:
** Utils for parsing
*/

#include "amazed.h"

/**
 * @brief Pour stocker toute les salles, je fais un tableau de structure.
 * Pour qu'on puisse les trouver facilement ; pour les chercher,
 * regardez dans /print/print_parsing.c comment j'ai pris les données
 * dans mon tableau de structure pour votre algo.
 *
 * @param maze
 * @param room
 */
void update_rooms_struct(maze_t *maze, room_t *room)
{
    int nb_ieme = 0;
    room_t **new;

    while (maze->rooms != NULL && maze->rooms[nb_ieme])
        nb_ieme++;
    new = malloc(sizeof(room_t *) * (nb_ieme + 2));
    if (!new)
        return;
    for (int j = 0; j < nb_ieme; j++)
        new[j] = maze->rooms[j];
    new[nb_ieme] = room;
    new[nb_ieme + 1] = NULL;
    if (maze->rooms)
        free(maze->rooms);
    maze->rooms = new;
}

/**
 * @brief Ici je prends les 3 données,
 * le premier le nom, le deuxième la position x et l'autre, la position y
 *
 * @param room
 * @param line
 */
void organize_data(room_t *room, char *line)
{
    int i = 0;

    while (line[i] == ' ')
        i++;
    room->name = my_strndup(line + i, ' ');
    while (line[i] && line[i] != ' ')
        i++;
    while (line[i] == ' ')
        i++;
    room->x_coord = my_getnbr(line + i);
    while (line[i] && line[i] != ' ')
        i++;
    while (line[i] == ' ')
        i++;
    room->y_coord = my_getnbr(line + i);
}

/**
 * @brief Ici c'est pour stocker les rooms et réinitialiser les flag des rooms.
 *
 * @param maze
 * @param line
 */
void add_room(maze_t *maze, char *line)
{
    room_t *room = malloc(sizeof(room_t));

    if (!room)
        return;
    organize_data(room, line);
    update_rooms_struct(maze, room);
    if (maze->parse_flag == 1)
        maze->start = room->name;
    if (maze->parse_flag == 2)
        maze->end = room->name;
    maze->parse_flag = 0;
}

/**
 * @brief Pour stocker tout les liens,
 * je fais un tableau de structure ici aussi.
 * Pour qu'on puisse les trouver facilement ; pour les chercher,
 * regardez dans /print/print_parsing.c comment j'ai pris les données
 * dans mon tableau de structure pour votre algo
 * (comme pour update_rooms_struct).
 *
 * @param maze
 * @param link
 */
void update_links_struct(maze_t *maze, link_t *link)
{
    int nb_ieme = 0;
    link_t **new;

    while (maze->links && maze->links[nb_ieme])
        nb_ieme++;
    new = malloc(sizeof(link_t *) * (nb_ieme + 2));
    if (!new)
        return;
    for (int j = 0; j < nb_ieme; j++)
        new[j] = maze->links[j];
    new[nb_ieme] = link;
    new[nb_ieme + 1] = NULL;
    if (maze->links != NULL)
        free(maze->links);
    maze->links = new;
}

/**
 * @brief Ici c'est pour stocker les lien des rooms.
 *
 * @param maze
 * @param line
 */
void add_link(maze_t *maze, char *line)
{
    link_t *link = malloc(sizeof(link_t));
    int i = 0;

    if (!link)
        return;
    link->first_room = my_strndup(line, '-');
    while (line[i] && line[i] != '-')
        i++;
    i++;
    link->second_room = my_strndup(line + i, '\n');
    update_links_struct(maze, link);
}
