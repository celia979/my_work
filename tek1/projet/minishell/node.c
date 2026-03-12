/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** Built-in dispatch table
*/

#include "mysh.h"

env_t *create_node(char *entry)
{
    env_t *node = malloc(sizeof(env_t));
    char *sep = my_strchr(entry, '=');

    if (!node)
        return NULL;
    node->next = NULL;
    if (!sep) {
        node->key = my_strdup(entry);
        node->value = my_strdup("");
        return node;
    }
    node->key = my_strndup(entry, sep - entry);
    node->value = my_strdup(sep + 1);
    return node;
}

env_t *parse_env(char **env)
{
    env_t *head = NULL;
    env_t *cur = NULL;
    env_t *node = NULL;
    int i = 0;

    if (!env)
        return NULL;
    while (env[i]) {
        node = create_node(env[i]);
        if (!node)
            return head;
        if (!head)
            head = node;
        else
            cur->next = node;
        cur = node;
        i++;
    }
    return head;
}

env_t *new_node(char const *key, char const *value)
{
    env_t *node = malloc(sizeof(env_t));

    if (!node)
        return NULL;
    node->key = my_strdup(key);
    node->value = my_strdup(value);
    node->next = NULL;
    return node;
}

void append_node(env_t **env, env_t *node)
{
    env_t *cur = *env;

    if (!cur) {
        *env = node;
        return;
    }
    while (cur->next)
        cur = cur->next;
    cur->next = node;
}

void free_node(env_t *cur)
{
    free(cur->key);
    free(cur->value);
    free(cur);
}
