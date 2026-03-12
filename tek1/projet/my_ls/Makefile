##
## EPITECH PROJECT, 2025
## my_ls
## File description:
## Makefile for my_ls project
##

CC = epiclang

SRC	=	my_ls.c			\
		ls_flag_a.c		\
		ls_flag_l.c		\
		ls_flag_d.c		\
		ls_flag_t.c		\
		ls_flag_r.c		\
		lib/my/my_putchar.c	\
		lib/my/my_put_nbr.c	\
		lib/my/my_putstr.c	\
		lib/my/my_strlen.c	\
		lib/my/my_strcpy.c	\
		lib/my/my_strcmp.c

OBJ	=	$(SRC:.c=.o)

NAME	=	my_ls

CFLAGS	=	-I./include -Wall -Wextra

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
