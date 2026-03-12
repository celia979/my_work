##
## EPITECH PROJECT, 2026
## Makefile
## File description:
## make my_top
##

CC	=	epiclang

SRC	=	main.c

OBJ	=	$(SRC:.c=.o)

NAME	=	my_top

CFLAGS	=	-I./include -Wextra -Wall -g

FLAG_LIB	=	-L./ -lmy

FLAG_NCURS	=	-lncurses

LIB_SRC	=	lib/my/my_intlen.c	\
		lib/my/str_manipulation/my_strcat.c	\
		lib/my/str_manipulation/my_strcmp.c	\
		lib/my/str_manipulation/my_strcpy.c	\
		lib/my/str_manipulation/my_strdup.c	\
		lib/my/str_manipulation/my_strlen.c	\
		lib/my/str_manipulation/my_strtof.c	\
		lib/my/str_manipulation/my_strtoi.c	\
		src/get_flag.c	\
		src/get_in_proc.c	\
		src/header/print_header.c	\
		src/header/print_in_header.c	\
		src/header/my_get_time.c	\
		src/header/my_get_users.c	\
		src/header/my_getloadavg.c	\
		src/header/my_getmemory.c	\
		src/header/my_getswap.c	\
		src/header/my_getcpu.c	\
		src/header/my_gettask.c	\
		src/header/count_state.c	\
		src/tab/get_user.c	\
		src/tab/get_fld.c	\
		src/tab/fill_task.c	\
		src/tab/print_tab.c	\
		src/tab/free_task.c	\

LIB_OBJ	=	$(LIB_SRC:.c=.o)

LIB_NAME	=	libmy.a

all:	$(NAME)

$(NAME):	$(OBJ)	\
		$(LIB_OBJ)
	ar rc $(LIB_NAME) $(LIB_OBJ)
	$(CC) -o $(NAME) $(OBJ) $(FLAG_LIB) $(FLAG_NCURS)

now:
	@clear
	make all
	@rm -f $(OBJ)
	@rm -f $(LIB_OBJ)
	@rm $(LIB_NAME)
	@echo ""
	@./my_top

vnow:	$(OBJ)	\
		$(LIB_OBJ)
	@ar rc $(LIB_NAME) $(LIB_OBJ)
	@$(CC) -o $(NAME) $(OBJ) $(FLAG_LIB) $(FLAG_NCURS)
	@rm -f $(OBJ)
	@rm -f $(LIB_OBJ)
	@rm $(LIB_NAME)
	@echo ""
	@valgrind --leak-check=full --log-file=log.txt ./my_top

clean:
	rm -f $(OBJ)
	rm -f $(LIB_OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all
