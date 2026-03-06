/*
** EPITECH PROJECT, 2025
** math
** File description:
** vecteur
*/

#include <unistd.h>
#include <math.h>
#include <stdio.h>

static int my_putchar(char c)
{
    write(1, &c, 1);
    return 1;
}

static int my_put_nbr(int nb)
{
    if (nb < 0) {
        my_putchar('-');
        nb = nb * -1;
    }
    if (nb >= 10) {
        my_put_nbr(nb / 10);
    }
    my_putchar((nb % 10) + '0');
    return 0;
}

static int vecteur_coordonne(int x, int y, int z)
{
    my_put_nbr(x);
    my_putchar(',');
    my_putchar(' ');
    my_put_nbr(y);
    my_putchar(',');
    my_putchar(' ');
    my_put_nbr(z);
    my_putchar('\n');
    return 0;
}

static int vecteur_sum_1(int x, int y, int z, int U)
{
    int a = x + U;
    int b = y + U;
    int c = z + U;

    my_put_nbr(a);
    my_putchar(',');
    my_putchar(' ');
    my_put_nbr(b);
    my_putchar(',');
    my_putchar(' ');
    my_put_nbr(c);
    my_putchar('\n');
    return 0;
}

static int vecteur_sum_2(int x, int y, int z, int V)
{
    int d = x + V;
    int e = y + V;
    int f = z + V;

    my_put_nbr(d);
    my_putchar(',');
    my_putchar(' ');
    my_put_nbr(e);
    my_putchar(',');
    my_putchar(' ');
    my_put_nbr(f);
    my_putchar('\n');
    return 0;
}

int vecteur_sum(int x, int y, int z, int U, int V)
{
    int a = x + U;
    int b = y + U;
    int c = z + U;
    int d = x + V;
    int e = y + V;
    int f = z + V;

    my_put_nbr(a + d);
    my_putchar(',');
    my_putchar(' ');
    my_put_nbr(b + e);
    my_putchar(',');
    my_putchar(' ');
    my_put_nbr(c + f);
    my_putchar('\n');
    return 0;
}

int vecteur_coef(int x, int y, int z, int m)
{
    int g = x * m;
    int h = y * m;
    int j = z * m;

    my_put_nbr(g);
    my_putchar(',');
    my_putchar(' ');
    my_put_nbr(h);
    my_putchar(',');
    my_putchar(' ');
    my_put_nbr(j);
    my_putchar('\n');
    return 0;
}

int vecteur_norme(int x, int y, int z, int V)
{
    int i = x * x;
    int o = y * y;
    int p = z * z;

    printf("%f", (sqrt(i)));
    my_putchar(',');
    my_putchar(' ');
    printf("%f", (sqrt(o)));
    my_putchar(',');
    my_putchar(' ');
    printf("%f", (sqrt(p)));
    my_putchar('\n');
    return 0;
}

int main(void)
{
    int x = 1;
    int y = 4;
    int z = 7;
    int U = 1;
    int V = 3;
    int m = 10;

    vecteur_coordonne(x, y, z);
    my_putchar('\n');
    vecteur_sum_1(x, y, z, U);
    my_putchar('\n');
    vecteur_sum_1(x, y, z, V);
    my_putchar('\n');
    vecteur_sum(x, y, z, U, V);
    my_putchar('\n');
    vecteur_coef(x, y, z, m);
    my_putchar('\n');
    vecteur_norme(x, y, z, V);
    return 0;
}
