/*
** EPITECH PROJECT, 2025
** Organized
** File description:
** Hardware structures and definitions
*/

#ifndef STRUCT_H
    #define STRUCT_H

typedef struct linked_list_s {
    void *data;
    struct linked_list_s *next;
} linked_list_t;

typedef enum hardware_type_e {
    ACTUATOR,
    DEVICE,
    PROCESSOR,
    SENSOR,
    WIRE
} hardware_type_t;

typedef struct hardware_s {
    hardware_type_t type;
    char *name;
    int id;
} hardware_t;

typedef struct sort_params_s {
    char **criteria;
    int *reverse_flags;
    int nb_criteria;
} sort_params_t;

int my_strlen(char const *str);
char *my_strdup(char *src);
int my_put_nbr(int nb);
int my_putstr(char const *str);
int my_strcmp(char const *s1, char const *s2);
int push_to_list(linked_list_t **begin, void *data);
char *get_type_string(hardware_type_t type);
hardware_type_t get_type_from_string(char const *str);

#endif /* STRUCT_H */
