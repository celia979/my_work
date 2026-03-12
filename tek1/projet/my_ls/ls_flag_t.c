/*
** EPITECH PROJECT, 2025
** my_ls
** File description:
** Flag -t implementation
*/

#include "include/my.h"

static void sort_by_time(file_info_t *files, int count)
{
    file_info_t tmp;
    int j = 0;
    int i = 1;

    while (i < count) {
        tmp = files[i];
        j = i - 1;
        while (j >= 0 && files[j].mtime < tmp.mtime) {
            files[j + 1] = files[j];
            j--;
        }
        files[j + 1] = tmp;
        i++;
    }
}

static void print_sorted(file_info_t *files, int count, int flags)
{
    int i = 0;

    while (i < count) {
        if (flags & FLAG_L)
            print_long_format(".", files[i].name);
        else {
            my_putstr(files[i].name);
            my_putchar(' ');
        }
        free(files[i].name);
        i++;
    }
    if (!(flags & FLAG_L))
        my_putchar('\n');
}

static int add_file(file_info_t *files, char const *filepath,
    char const *name, int count)
{
    char path[1024];

    my_strcpy(path, filepath);
    my_strcpy(path + my_strlen(path), "/");
    my_strcpy(path + my_strlen(path), name);
    files[count].name = malloc(my_strlen(name) + 1);
    my_strcpy(files[count].name, name);
    lstat(path, &files[count].info);
    files[count].mtime = files[count].info.st_mtime;
    return count + 1;
}

static int fill_files(DIR *dir, file_info_t *files,
    char const *filepath, int flags)
{
    struct dirent *entry = readdir(dir);
    int count = 0;

    while (entry != NULL) {
        if (!(flags & FLAG_A) && entry->d_name[0] == '.') {
            entry = readdir(dir);
            continue;
        }
        count = add_file(files, filepath, entry->d_name, count);
        entry = readdir(dir);
    }
    return count;
}

int flag_t(char const *filepath, int flags)
{
    DIR *dir = opendir(filepath);
    file_info_t *files = malloc(sizeof(file_info_t) * 128);
    int count = 0;

    if (dir == NULL)
        return error(filepath);
    count = fill_files(dir, files, filepath, flags);
    closedir(dir);
    sort_by_time(files, count);
    print_sorted(files, count, flags);
    free(files);
    return 0;
}
