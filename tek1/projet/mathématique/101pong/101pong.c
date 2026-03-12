/*
** EPITECH PROJECT, 2025
** 101 pong
** File description:
** 101 pong
*/

#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int my_putchar(char c)
{
    write(1, &c, 1);
    return 0;
}

static int my_putstr(char const *str)
{
    int i = 0;

    while (str[i] != '\0') {
        my_putchar(str[i]);
        i = i + 1;
    }
    return 0;
}

static void my_put_float(double nb)
{
    int entier = (int)nb;
    double decimale = nb - entier;

    if (nb < 0) {
        my_putchar('-');
        entier = -entier;
        decimale = -decimale;
    }
    if (entier >= 10)
        my_put_float(entier / 10);
    my_putchar((entier % 10) + '0');
    my_putchar('.');
    decimale = decimale * 100;
    entier = (int)decimale;
    my_putchar((entier / 10) + '0');
    my_putchar((entier % 10) + '0');
}

static void afficher_vitesse(double *v)
{
    my_putstr("The velocity vector of the ball is:\n(");
    my_put_float(v[0]);
    my_putstr(", ");
    my_put_float(v[1]);
    my_putstr(", ");
    my_put_float(v[2]);
    my_putstr(")\n");
}

static void afficher_position(double *pos, int n)
{
    my_putstr("At time t + ");
    printf("%d", n);
    my_putstr(", ball coordinates will be:\n(");
    my_put_float(pos[0]);
    my_putstr(", ");
    my_put_float(pos[1]);
    my_putstr(", ");
    my_put_float(pos[2]);
    my_putstr(")\n");
}

static void afficher_angle(double *v)
{
    double norme_xy = sqrt(v[0] * v[0] + v[1] * v[1]);
    double norme = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    double angle = asin(norme_xy / norme) * 180.0 / M_PI;

    my_putstr("The incidence angle is:\n");
    my_put_float(angle);
    my_putstr(" degrees\n");
}

static void calculer_pong(double *p0, double *p1, int n)
{
    double v[3];
    double pos[3];

    v[0] = p1[0] - p0[0];
    v[1] = p1[1] - p0[1];
    v[2] = p1[2] - p0[2];
    pos[0] = p1[0] + v[0] * n;
    pos[1] = p1[1] + v[1] * n;
    pos[2] = p1[2] + v[2] * n;
    afficher_vitesse(v);
    afficher_position(pos, n);
    if (v[2] < 0)
        afficher_angle(v);
    else
        my_putstr("The ball won't reach the paddle.\n");
}

int main(int ac, char **av)
{
    double p0[3];
    double p1[3];
    int n = 0;

    if (ac != 8)
        return 84;
    p0[0] = atof(av[1]);
    p0[1] = atof(av[2]);
    p0[2] = atof(av[3]);
    p1[0] = atof(av[4]);
    p1[1] = atof(av[5]);
    p1[2] = atof(av[6]);
    n = atoi(av[7]);
    if (n < 0)
        return 84;
    calculer_pong(p0, p1, n);
    return 0;
}
