/*
** EPITECH PROJECT, 2026
** my_top
** File description:
** get current time and uptime information
*/

#include "my.h"

static void get_uptime_string(long uptime, char *buffer)
{
    long days = uptime / 86400;
    long hours = (uptime % 86400) / 3600;
    long minutes = (uptime % 3600) / 60;

    buffer[0] = '\0';
    if (days > 0) {
        sprintf(buffer, "%ld day%s, ", days, days > 1 ? "s" : "");
    }
    if (hours > 0) {
        sprintf(buffer + my_strlen(buffer), "%ld:%02ld", hours, minutes);
    } else {
        sprintf(buffer + my_strlen(buffer), "%ld min", minutes);
    }
}

int my_get_time(time_info_t *info)
{
    time_t now = 0;
    struct tm *tm_info = NULL;
    FILE *file = NULL;
    double uptime_seconds = 0;

    time(&now);
    tm_info = localtime(&now);
    info->hour = tm_info->tm_hour;
    info->min = tm_info->tm_min;
    info->sec = tm_info->tm_sec;
    file = fopen("/proc/uptime", "r");
    if (file == NULL)
        return 84;
    fscanf(file, "%lf", &uptime_seconds);
    fclose(file);
    info->uptime = (long)uptime_seconds;
    get_uptime_string(info->uptime, info->uptime_str);
    return 0;
}
