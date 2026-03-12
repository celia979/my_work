/*
** EPITECH PROJECT, 2026
** my_top
** File description:
** struct
*/

#ifndef STRUCT
    #define STRUCT

typedef struct flag_s
{
    int error;
    int nb_refresh;
    double spr;         //seconde par refresh
    char *user;
} flag_t;


typedef struct time_info_s {
    int hour;
    int min;
    int sec;
    long uptime;
    char uptime_str[128];
} time_info_t;

typedef struct system_info_s {
    double loadavg[3];
    double mem[5];
    double swap[4];
    double cpu[7];
    double task[5];
    double prev_cpu[7];
} system_info_t;

typedef struct task
{
    char *pid;
    char *uid;
    char *file_path_stat;
    char *fpath_status;
    char *user;
    char *priority;
    char *niceness;
    int virt;
    int res;
    int shr;
    char *stat;
    double cpu_use;
    double mem_use;
    int time;
    char *cmd_name;
}task_t;


#endif /* STRUCT */
