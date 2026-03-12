/*
** EPITECH PROJECT, 2026
** A-Maze-d
** File description:
** Select optimal paths for N robots
*/

/*Eiffel Tower;Paris;France
Colosseum;Rome;Italy
Great Pyramid;Giza;Egypt
 
Did you visit the Eiffel Tower ? It's in France, in Paris !
Did you visit the Colosseum ? It's in Italy, in Rome !
Did you visit the Great Pyramid ? It's in Egypt, in Giza !
*/
int clear(char const *str, int i)
{
    if (str[i + 1] == ';')
        if (str[i] == "")
            printf("It's in France")
}

int print(char const *str)
{
    for (int i = 0; str[i] != "\n"; i++) {
        if (str[i] == "Eiffel Tower")
            printf("Did you visit the Eiffel Tower ?");
            clear(str);
        if (str[i] == "Colosseum")
            printf("Did you visit the Colosseum ?");
        if (str[i] == "Great Pyramid")
            printf("Did you visit the Great Pyramid ?");
    }

    return 0;
}
