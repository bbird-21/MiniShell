
NAME	= minishell

SRC		=	srcs/get_next_line.c \
			srcs/get_next_line_utils.c \
			srcs/split.c \
			srcs/split_utils.c \
			srcs/tokenisation.c \
			srcs/utils.c \
			srcs/inutils.c \
			srcs/trash.c \
			srcs/main.c

OBJS    = ${SRC:.c=.o}

OPTION 	= -I ./inc/

CC		= gcc
RM		= rm -f

CFLAGS	= -Wall -Wextra -Werror


.c.o:
			${CC} -lreadline -c ${CFLAGS} ${OPTION} $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			${CC} -o ${NAME} ${OBJS}

all:		${NAME}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY: all clean fclean re
