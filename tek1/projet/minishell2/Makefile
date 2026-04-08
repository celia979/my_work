##
## EPITECH PROJECT, 2026
## minishell2
## File description:
## Makefile for mysh - minishell2
##

CC	=	epiclang

CFLAGS	=	-Wall -Wextra

NAME	=	mysh

SRC	=	main.c					\
		lib/my_lib.c				\
		lib/my_str.c				\
		src/shell.c				\
		src/env_utils.c				\
		src/parse.c				\
		src/path.c				\
		src/exec.c				\
		src/node.c				\
		src/builtins/builtins.c			\
		src/builtins/builtins_env.c		\
		src/builtins/builtins_dispatch.c	\
		src/pipe/cmd_redir.c			\
		src/pipe/cmd_parse.c			\
		src/pipe/cmd_exec.c			\
		src/pipe/pipeline_parse.c		\
		src/pipe/pipeline_exec.c		\
		src/pipe/pipeline_free.c		\
		src/pipe/redir.c

OBJ	=	$(SRC:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

now:
	@clear
	make all
	@rm -f $(OBJ)
	@echo ""
	@./mysh

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re

