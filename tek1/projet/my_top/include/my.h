/*
** EPITECH PROJECT, 2026
** fctn
** File description:
** renseigner tout les fctn different
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <time.h>
#include <dirent.h>
#include <utmp.h>
#include "struct.h"

#ifndef FCTN
    #define FCTN

flag_t *get_flag(char **av);

//info should be in format (Name: Value ....)
double get_value_in_proc(char *what, char *where);
char *get_str_in_proc(char *what, char *where);


//----|header fonction|----

// load information and put in double * gived
void fill_system_info(system_info_t *sys);
int my_getloadavg(double loadavg[]);//double [3]
int my_getmemory(double mem[]);//double [5]
int my_getswap(double swap[]);//double [4]
int my_getcpu(double cpu[], double prev[]);
void calculate_cpu(double *cpu, double *stats, double *prev);
int my_gettask(double task[]); // total, running, sleeping, stopped, zombie

//----time and uptime----
int my_get_time(time_info_t *info);
int my_get_users(void);

//----print info----
int print_header(system_info_t *sys);
int count_state(char state);
int print_tasks_line(double task[]);
int print_cpu_line(double cpu[]);
int print_mem_line(double mem[]);
int print_swap_line(double swap[], double mem[]);
int print_top_line(time_info_t *info, int users, double avg[]);


// ----|tab fonction|----
task_t **take_fld(char *pathfolder);
char *get_user(char *uid);
int fill_task(task_t **task_lst);
int print_tab(task_t **fld_lst, char *user);
int free_task(task_t **task_lst);


//----|str manipulation|----
char *my_strcat(char *s1, char const *s2);
int my_strcmp(char const *s1, char const *s2);
char *my_strdup(char *str);
int my_strlen(char const *str);
char *my_strcpy(char *dest, char const *src);
int my_strtoi(char *str);
double my_strtof(char *str);

int my_intlen(int nb);

#endif
