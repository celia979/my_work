##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## make my_hunter
##

CC	=	epiclang

CFLAGS	=	-I./../../include -Wextra -Wall -g

LIB_SRC	=	my_strcat.c	\
		my_strcmp.c	\
		my_strcpy.c	\
		my_strdup.c	\
		my_strlen.c	\
		my_strtof.c	\
		my_strtoi.c	\

LIB_OBJ	=	$(LIB_SRC:.c=.o)

LIB_NAME	=	libstr.a

all:	$(LIB_NAME)

$(LIB_NAME):	$(LIB_OBJ)
	ar rc $(LIB_NAME) $(LIB_OBJ)
	mv libstr.a ../../libstr.a

clean:
	rm -f $(OBJ)
	rm -f $(LIB_OBJ)

fclean:	clean
	rm -f ../../$(LIB_NAME)

re:	fclean all
