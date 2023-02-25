
NAME	= minishell

SRC		=	srcs/first_split.c \
			srcs/split_utils.c \
			srcs/tokenisation.c \
			srcs/utils.c \
			srcs/inutils.c \
			srcs/trash.c \
			srcs/main.c \
			srcs/parse_error.c \
			srcs/cmd_creator.c \
			srcs/env.c \
			srcs/lst_utils.c \
			builtins/pwd.c \
			builtins/export.c \
			builtins/env.c \
			builtins/unset.c

OBJS    = ${SRC:.c=.o}

OPTION 	= -I ./inc/

CC		= cc
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
