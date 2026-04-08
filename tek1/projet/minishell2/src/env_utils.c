/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** Environment linked-list utility functions
*/

#include "../include/mysh.h"

void free_env(env_t *env)
{
    env_t *next = NULL;

    while (env) {
        next = env->next;
        free(env->key);
        free(env->value);
        free(env);
        env = next;
    }
}

char *get_env_value(env_t *env, char const *key)
{
    env_t *cur = env;

    while (cur) {
        if (my_strcmp(cur->key, key) == 0)
            return cur->value;
        cur = cur->next;
    }
    return NULL;
}

static int update_existing(env_t *cur, char const *key, char const *value)
{
    while (cur) {
        if (my_strcmp(cur->key, key) == 0) {
            free(cur->value);
            cur->value = my_strdup(value);
            return 1;
        }
        if (!cur->next)
            break;
        cur = cur->next;
    }
    return 0;
}

int set_env_value(env_t **env, char const *key, char const *value)
{
    env_t *node = NULL;

    if (update_existing(*env, key, value))
        return 0;
    node = new_node(key, value);
    if (!node)
        return 1;
    append_node(env, node);
    return 0;
}

int unset_env_value(env_t **env, char const *key)
{
    env_t *cur = *env;
    env_t *prev = NULL;

    while (cur) {
        if (my_strcmp(cur->key, key) != 0) {
            prev = cur;
            cur = cur->next;
            continue;
        }
        if (prev)
            prev->next = cur->next;
        else
            *env = cur->next;
        free_node(cur);
        return 0;
    }
    return 0;
}

static char *build_entry(env_t *cur)
{
    return my_strjoin(cur->key, cur->value, '=');
}

static int count_env(env_t *env)
{
    int count = 0;

    while (env) {
        count++;
        env = env->next;
    }
    return count;
}

char **env_to_array(env_t *env)
{
    char **arr = malloc(sizeof(char *) * (count_env(env) + 1));
    env_t *cur = env;
    int i = 0;

    if (!arr)
        return NULL;
    while (cur) {
        arr[i] = build_entry(cur);
        if (!arr[i]) {
            arr[i] = NULL;
            return arr;
        }
        i++;
        cur = cur->next;
    }
    arr[i] = NULL;
    return arr;
}
