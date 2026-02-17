##
## EPITECH PROJECT, 2026
## B-CPE-210
## File description:
## Makefile
##

CC	=	epiclang

SRC	=	main.c		\
		utils.c

OBJ	=	$(SRC:.c=.o)

NAME	=	frenchNameFormatter

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
