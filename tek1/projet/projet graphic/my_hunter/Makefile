##
## EPITECH PROJECT, 2025
## my_hunter
## File description:
## Makefile
##

SRC	=	my_hunter.c		\
		animation.c		\
		destroy_enemy.c		\
		enemy_manager.c     \
        create_enemy.c

OBJ	=	$(SRC:.c=.o)

NAME	=	my_hunter

CFLAGS	=	-Wall -Wextra -I./

LDFLAGS	=	-lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio -lm

all:	$(NAME)

$(NAME):	$(OBJ)
	cc -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
