/*
** EPITECH PROJECT, 2025
** Setting Up
** File description:
** markefile
*/

SRC	=	main.c		\
		map_loader.c	\
		map_generator.c	\
		solver.c	\
		my_lib.c

OBJ	=	$(SRC:.c=.o)

NAME	=	setting_up

CFLAGS	=	-Wall -Wextra -I.

all:	$(NAME)

$(NAME):	$(OBJ)
	epiclang -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all
