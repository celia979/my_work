/*
** EPITECH PROJECT, 2025
** my_ls
** File description:
** Flag -l implementation
*/

#include "include/my.h"

void print_permissions(mode_t mode)
{
    my_putchar((S_ISDIR(mode)) ? 'd' : '-');
    my_putchar((mode & S_IRUSR) ? 'r' : '-');
    my_putchar((mode & S_IWUSR) ? 'w' : '-');
    my_putchar((mode & S_IXUSR) ? 'x' : '-');
    my_putchar((mode & S_IRGRP) ? 'r' : '-');
    my_putchar((mode & S_IWGRP) ? 'w' : '-');
    my_putchar((mode & S_IXGRP) ? 'x' : '-');
    my_putchar((mode & S_IROTH) ? 'r' : '-');
    my_putchar((mode & S_IWOTH) ? 'w' : '-');
    my_putchar((mode & S_IXOTH) ? 'x' : '-');
}

static void print_time(time_t mtime)
{
    char *time_str = ctime(&mtime);
    int i = 4;

    while (i < 16) {
        my_putchar(time_str[i]);
        i++;
    }
}

static void build_path(char *path, char const *filepath, char const *name)
{
    int len = 0;

    if (filepath[0] == '.' && filepath[1] == '\0') {
        my_strcpy(path, name);
        return;
    }
    len = my_strlen(filepath);
    my_strcpy(path, filepath);
    if (len > 0 && path[len - 1] != '/') {
        path[len] = '/';
        path[len + 1] = '\0';
    }
    len = my_strlen(path);
    my_strcpy(path + len, name);
}

static void print_file_info(struct stat *info, char const *name)
{
    struct passwd *pwd = getpwuid(info->st_uid);
    struct group *grp = getgrgid(info->st_gid);

    my_putchar(' ');
    my_put_nbr(info->st_nlink);
    my_putchar(' ');
    my_putstr(pwd ? pwd->pw_name : "unknown");
    my_putchar(' ');
    my_putstr(grp ? grp->gr_name : "unknown");
    my_putchar(' ');
    my_put_nbr(info->st_size);
    my_putchar(' ');
    print_time(info->st_mtime);
    my_putchar(' ');
    my_putstr(name);
    my_putchar('\n');
}

void print_long_format(char const *filepath, char const *name)
{
    struct stat info;
    char path[1024];

    build_path(path, filepath, name);
    if (lstat(path, &info) == -1) {
        perror(path);
        return;
    }
    print_permissions(info.st_mode);
    print_file_info(&info, name);
}

int flag_l(char const *filepath, int flags)
{
    return flag_a(filepath, flags | FLAG_L);
}
