
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

CC		= clang
RM		= rm -f

CFLAGS	= -Wall -Wextra -Werror -g3


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

malloc_test: $(OBJS)
	$(CC) $(CFLAGS) -fsanitize=undefined -rdynamic -o $@ ${OBJS} -L/usr/local/lib -I/usr/local/include -lreadline -L. -lmallocator

.PHONY: all clean fclean re
