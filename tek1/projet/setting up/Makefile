##
## EPITECH PROJECT, 2025
## Setting Up
## File description:
## Makefile
##

CC = epiclang

SRC	=	main.c		\
		map_loader.c	\
		file_parser.c	\
		map_generator.c	\
		solver.c	\
		my_lib.c

OBJ	=	$(SRC:.c=.o)

NAME	=	setting_up

CFLAGS	=	-Wall -Wextra -I.

all:	$(NAME)

$(NAME):	$(OBJ)
	cc -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
