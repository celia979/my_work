##
## EPITECH PROJECT, 2025
## my_radar
## File description:
## Makefile for my_radar project
##

SRC	=	my_radar.c			\
		file_parser.c		\
		parser.c			\
		tower_manager.c		\
		param_game.c		\
		airplane_manager.c	\
		airplane_logic.c	\
		collision.c			\
		destroy_airplane.c	\
		airplane_spawner.c	\
		texture.c			\
		parse_utils.c		\
		circle_manager.c

OBJ	=	$(SRC:.c=.o)

NAME	=	my_radar

CC	=	epiclang

CFLAGS	=	-I./include -W -Wall -Wextra

LDFLAGS	=	-lcsfml-graphics -lcsfml-system -lcsfml-window -lm

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
