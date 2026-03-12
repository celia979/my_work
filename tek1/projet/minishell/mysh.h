/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** Main header for mysh
*/

#ifndef MYSH_H
    #define MYSH_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/wait.h>
    #include <sys/stat.h>
    #include <dirent.h>
    #include <signal.h>

    #define PROMPT "$> "
    #define SUCCESS 0

typedef struct env_s {
    char *key;
    char *value;
    struct env_s *next;
} env_t;

typedef struct shell_s {
    env_t *env;
    int last_status;
} shell_t;

shell_t *init_shell(char **env);
void destroy_shell(shell_t *shell);
void run_shell(shell_t *shell);

env_t *parse_env(char **env);
void free_env(env_t *env);
char *get_env_value(env_t *env, char const *key);
int set_env_value(env_t **env, char const *key, char const *value);
int unset_env_value(env_t **env, char const *key);
char **env_to_array(env_t *env);

char **split_args(char const *line);
void free_args(char **args);
char *find_binary(char *cmd, char **env);

int execute_command(char **args, shell_t *shell);
int is_builtin(char const *cmd);
int exec_builtin(char **args, shell_t *shell);

int builtin_cd(char **args, shell_t *shell);
int builtin_setenv(char **args, shell_t *shell);
int builtin_unsetenv(char **args, shell_t *shell);
int builtin_env(char **args, shell_t *shell);
int builtin_exit(char **args, shell_t *shell);

int my_strlen(char const *s);
int my_strcmp(char const *s1, char const *s2);
int my_strncmp(char const *s1, char const *s2, int n);
char *my_strdup(char const *s);
char *my_strndup(char const *s, int n);
char *my_strchr(char const *s, char c);
char *my_strjoin(char const *s1, char const *s2, char sep);
void my_strcpy(char *dst, char const *src);
void my_strcat(char *dst, char const *src);
int my_atoi(char const *s);

void free_node(env_t *cur);
void append_node(env_t **env, env_t *node);
env_t *new_node(char const *key, char const *value);
env_t *create_node(char *entry);

#endif
