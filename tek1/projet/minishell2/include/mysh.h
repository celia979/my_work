/*
** EPITECH PROJECT, 2024
** minishell2
** File description:
** Main header for mysh - minishell2
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
    #include <fcntl.h>
    #include <dirent.h>
    #include <signal.h>
    #include <errno.h>

    #define PROMPT "$> "

typedef struct env_s {
    char *key;
    char *value;
    struct env_s *next;
} env_t;

typedef struct shell_s {
    env_t *env;
    int last_status;
} shell_t;

typedef struct redir_s {
    char *in_file;
    char *out_file;
    char *heredoc;
    int append;
} redir_t;

typedef struct cmd_s {
    char **args;
    redir_t redir;
    struct cmd_s *next;
} cmd_t;

typedef struct pipeline_s {
    cmd_t *cmds;
    struct pipeline_s *next;
} pipeline_t;

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

pipeline_t *parse_line(char *line);
cmd_t *parse_segment(char *segment);
void free_pipeline_list(pipeline_t *list);
void free_cmd(cmd_t *cmd);

int is_redir_tok(char const *tok);
void apply_redir(redir_t *redir, char const *op, char const *file);
void fill_cmd_args(cmd_t *cmd, char **toks);

int run_pipeline_list(shell_t *shell, pipeline_t *list);
int run_pipeline(shell_t *shell, pipeline_t *pipeline);
int run_cmd(shell_t *shell, cmd_t *cmd);
int setup_redirections(redir_t const *redir);

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
