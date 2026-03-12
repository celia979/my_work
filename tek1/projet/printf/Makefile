##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## Makefile
##

CC      =   epiclang

SRC     =   lib/my/my_putchar.c \
            lib/my/my_put_nbr.c \
            lib/my/my_putstr.c \
            lib/my/my_strlen.c \
            lib/my/get_nb_len.c \
            lib/my/my_printf.c \
            my_put_unsigned.c \
            my_put_hex.c \
            my_put_octal.c \
            my_put_pointer.c \
            my_put_float.c \
            my_put_long.c \
            my_put_binary.c \
            my_put_e.c \
            my_put_g.c \
            width.c \
            length.c \
            precision.c \
            flags.c \
            tools.c

OBJ     =   $(SRC:.c=.o)

NAME    =   libmy.a

CFLAGS  =   -I./include

all:    $(NAME)

$(NAME):    $(OBJ)
	ar rc $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:     fclean all

.PHONY: all clean fclean re
