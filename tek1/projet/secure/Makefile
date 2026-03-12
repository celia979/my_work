##
## EPITECH PROJECT, 2026
## Makefile
## File description:
## make project
##

CC	=	epiclang

SRC	=	main.c

OBJ     =       $(SRC:.c=.o)

NAME    =       secured

CFLAGS	=	-I./include -Wextra -Wall -g

FLAG_LIB	=	-L./ libhashtable.a

LIB_SRC	=	lib/str/my_strcat.c	\
		lib/str/my_strcmp.c	\
		lib/str/my_strcpy.c	\
		lib/str/my_strdup.c	\
		lib/str/my_strlen.c	\
		lib/str/my_strtof.c	\
		lib/str/my_strtoi.c	\
		lib/print.c	\
		src/delete_hashtable.c	\
		src/free_elem.c	\
		src/get_hashsize.c	\
		src/hash.c	\
		src/ht_delete.c	\
		src/ht_dump.c	\
		src/ht_insert.c	\
		src/ht_search.c	\
		src/new_hashtable.c	\

LIB_OBJ	=	$(LIB_SRC:.c=.o)

LIB_NAME	=	libhashtable.a

all:	$(NAME)

$(NAME):	$(LIB_OBJ)
	ar rc $(LIB_NAME) $(LIB_OBJ)

now:	$(OBJ)	\
		$(LIB_OBJ)
	@echo "\n"
	@ar rc $(LIB_NAME) $(LIB_OBJ)
	@$(CC) -o test $(OBJ) $(FLAG_LIB)
	@valgrind ./test

renow: re	\
		now

clean:
	rm -f $(OBJ)
	rm -f $(LIB_OBJ)

fclean:
	rm -f $(OBJ)
	rm -f $(LIB_OBJ)
	rm -f $(LIB_NAME)
	rm -f $(NAME)

re:	fclean all