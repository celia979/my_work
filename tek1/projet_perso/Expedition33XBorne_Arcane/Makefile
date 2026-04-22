##
## EPITECH PROJECT, 2025
## my_radar
## File description:
## Makefile for my_radar project
##

CC      = gcc
CFLAGS  = -Wall -Wextra -O2 -std=c11
LIBS    = $(shell sdl2-config --cflags --libs) -lSDL2_ttf -lm

NAME  = expedition33

SRC    =	main.c	\
			game.c

OBJ	=	$(SRC:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBS)

now:
	@clear
	make all
	@rm -f $(OBJ)
	@echo ""
	@./expedition33

vnow:	$(OBJ)
	@$(CC) -o $(NAME) $(OBJ) $(LIBS) $(CFLAGS)
	@rm -f $(OBJ)
	@echo ""
	@valgrind --leak-check=full --log-file=log.txt ./expedition33


clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re