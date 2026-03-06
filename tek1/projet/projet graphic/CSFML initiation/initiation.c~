/*
** EPITECH PROJECT, 2025
** csfml
** File description:
** initiation
*/

#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <stdlib.h>

int pollevent(sfRenderWindow *window)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(window, &event))
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(window);
    return 0;
}

int main(void)
{
    sfRenderWindow *window;
    sfVideoMode mode = {800, 600};
    sfEvent event;
    sfTexture *texture;
    sfSprite *sprite;

    texture = sfTexture_createFromFile("cat.jpeg", NULL);
    window = sfRenderWindow_create(mode, "SFML window", sfResize | sfClose, NULL);
    if (!window)
        return -1;
    if (!texture)
        return -1;
    sprite = sfSprite_create();
    sfSprite_setTexture(sprite, texture, sfTrue);
    while (sfRenderWindow_isOpen(window)) {
        sfRenderWindow_clear(window, sfBlack);
        sfRenderWindow_drawSprite(window, sprite, NULL);
        sfRenderWindow_display(window);
        pollevent(window);
    }
    sfRenderWindow_destroy(window);
    sfTexture_destroy(texture);
    sfSprite_destroy(sprite);
    return 0;
}
