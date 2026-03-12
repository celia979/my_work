/*
** EPITECH PROJECT, 2026
** my_top
** File description:
** get load avg
*/

#include "my.h"

int my_strisnum(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] <= '0' || '9' <= str[i])
            return 1;
    return 0;
}

int nb_of_dir(char *pathfolder)
{
    DIR *dir;
    struct dirent *dirent;
    int size = 0;

    dir = opendir(pathfolder);
    for (dirent = readdir(dir); dirent != NULL; dirent = readdir(dir))
        if (my_strisnum(dirent->d_name) == 0)
            size += 1;
    closedir(dir);
    return size;
}

task_t **take_fld(char *pathfolder)
{
    DIR *dir;
    struct dirent *dirent;
    task_t **task_list = malloc(sizeof(task_t *) * (nb_of_dir(pathfolder) + 1));
    task_t *task;
    int position = 0;

    if (task_list == NULL)
        return NULL;
    dir = opendir(pathfolder);
    for (dirent = readdir(dir); dirent != NULL; dirent = readdir(dir))
        if (my_strisnum(dirent->d_name) == 0) {
            task = malloc(sizeof(task_t) * 1);
            task->file_path_stat = my_strcat(dirent->d_name, "/stat");
            task->fpath_status = my_strcat(dirent->d_name, "/status");
            task_list[position] = task;
            position += 1;
        }
    closedir(dir);
    task_list[position] = NULL;
    return task_list;
}
