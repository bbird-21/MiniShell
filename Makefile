
NAME	= minishell

SRC		=	srcs/split.c \
			srcs/split_utils.c \
			srcs/tokenisation.c \
			srcs/utils.c \
			srcs/inutils.c \
			srcs/trash.c \
			srcs/main.c \
			srcs/parse_error.c \
			srcs/cmd_creator.c

OBJS    = ${SRC:.c=.o}

OPTION 	= -I ./inc/

CC		= gcc -g3
RM		= rm -f

CFLAGS	= -Wall -Wextra -Werror


.c.o:
			${CC} -c ${CFLAGS} ${OPTION} $< -o ${<:.c=.o}

${NAME}:	${OBJS} Makefile
			${CC} -o ${NAME} ${OBJS} -L/usr/local/lib -I/usr/local/include -lreadline

all:		${NAME}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY: all clean fclean re
