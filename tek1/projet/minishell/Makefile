##
## EPITECH PROJECT, 2024
## minishell1
## File description:
## Makefile for mysh
##

CC = epiclang
CFLAGS = -Wall -Wextra -I./include
NAME = mysh

SRC =	main.c \
	my_lib.c	\
	my_str.c	\
	shell.c \
	env_utils.c \
	parse.c \
	path.c \
	exec.c \
	node.c	\
	builtins.c \
	builtins_env.c \
	builtins_dispatch.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

now:
	@clear
	make all
	@rm -f $(OBJ)
	@echo ""
	@./mysh

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
