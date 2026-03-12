##
## EPITECH PROJECT, 2025
## Organized
## File description:
## Makefile
##

CC	=	epiclang

SRC	=	my_lib.c	\
		node.c		\
		add.c		\
		del.c		\
		disp.c		\
		sort.c		\
		organized.c

OBJ	=	$(SRC:.c=.o)

NAME	=	organized

CFLAGS	=	-Wall -Wextra -I.

all:	$(NAME)

$(NAME):	$(OBJ) libshell.a
	$(CC) -o $(NAME) $(OBJ) -L. -lshell

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
