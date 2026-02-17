##
## EPITECH PROJECT, 2026
## US Name Formatter
## File description:
## Makefile
##

CC	=	epiclang

SRC	=	main.c  \
        my_lib.c

OBJ	=	$(SRC:.c=.o)

NAME	=	USNameFormatter

CFLAGS	=	-W -Wall -Wextra

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
