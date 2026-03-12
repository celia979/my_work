/*
** EPITECH PROJECT, 2026
** my_put_pointer
** File description:
** yes
*/

#include "my.h"

static int my_put_ptr_hex(unsigned long nb)
{
    char *base = "0123456789abcdef";
    int count = 0;

    if (nb >= 16) {
        count += my_put_ptr_hex(nb / 16);
    }
    count += my_putchar(base[nb % 16]);
    return count;
}

int my_put_pointer(void *ptr)
{
    unsigned long addr = (unsigned long)ptr;
    int count = 0;

    if (ptr == ((void *)0)) {
        count += my_putstr("(nil)");
        return count;
    }
    count += my_putstr("0x");
    count += my_put_ptr_hex(addr);
    return count;
}
