##
## EPITECH PROJECT, 2026
## Makefile
## File description:
## Makefile of project
##

CC = 	epiclang

CFLAGS	= -Wall -Wextra -I./include

SRC	=	lib/my/mini_printf.c	\
		lib/my/my_getnbr.c	\
		lib/my/my_put_nbr.c	\
		lib/my/my_putchar.c	\
		lib/my/my_putstr.c	\
		lib/my/my_strcmp.c	\
		lib/my/my_strlen.c	\
		lib/my/my_strndup.c	\
		src/moves/initilize_robots.c	\
		src/moves/move_robots.c	\
		src/parse/parse_analyze.c	\
		src/parse/parse_utils.c	\
		src/parse/parse.c	\
		src/path/path_bfs.c	\
		src/path/path_select.c	\
		src/path/path_rebuild.c	\
		src/print/print_parsing.c	\
		src/free.c	\
		src/main.c

OBJ	=	$(SRC:.c=.o)

NAME	=	amazed

all:	$(NAME)

$(NAME):	$(OBJ)
	@$(CC) -o $(NAME) $(OBJ)
	@make clean
	@echo "Everything is compiled"

clean:
	@rm -f $(OBJ)

fclean:	clean
	@rm -f $(NAME)
	@echo "Everything is cleaned"

map: fclean
	@rm input

re:	clean all
