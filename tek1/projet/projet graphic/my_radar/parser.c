/*
** EPITECH PROJECT, 2025
** csfml
** File description:
** my radar
*/

#include "./my.h"

int validate_file(char const *filepath)
{
    FILE *file = fopen(filepath, "r");

    if (!file) {
        write(1, "Error: script file not found\n", 30);
        return 84;
    }
    fclose(file);
    return 0;
}

static script_data_t *cleanup_on_error(script_data_t *script, int stage)
{
    if (stage >= 2)
        free(script->airplanes);
    if (stage >= 3)
        free(script->towers);
    free(script);
    return NULL;
}

static script_data_t *allocate_script(char const *filepath)
{
    script_data_t *script = malloc(sizeof(script_data_t));

    if (!script)
        return NULL;
    script->airplane_count = count_lines(filepath, 'A');
    script->tower_count = count_lines(filepath, 'T');
    return script;
}

script_data_t *parse_script_file(char const *filepath)
{
    script_data_t *script = allocate_script(filepath);

    if (!script)
        return NULL;
    if (validate_counts(script) == 84)
        return cleanup_on_error(script, 1);
    if (allocate_script_data(script) == 84)
        return cleanup_on_error(script, 1);
    if (read_script_content(filepath, script) == 84)
        return cleanup_on_error(script, 3);
    return script;
}
