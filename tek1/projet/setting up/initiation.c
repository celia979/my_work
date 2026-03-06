/*
** EPITECH PROJECT, 2025
** csfml
** File description:
** initiation
*/

#include <SFML/Graphics.h>

int  pollevent(void)
{
    while (sfRenderWindow_pollEvent(window, &event))
        if (event.type == sfevtClosed)
            sfRenderWindowClose(window);
}

int main(void)
{
    sfRenderWindow *window;
    sfVideoMode mode = {800, 600};

    window = sfRenderWindow_create(mode, "SFML window", sfResize | sfClose, NULL);
    while (sfRenderWindow_isOpen(window)) {
        sfRenderWindow_display(window);
        pollevent();
    }
    sfRenderWindow_destroy(window);
    return 0;
}
