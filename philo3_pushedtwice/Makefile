CC		= gcc -g

CFLAGS		= -Wall -Werror -Wextra

NAME		= philo

INC		= ./inc/

LIB_NAME	= libft/libft.a

SRCS		= $(wildcard ./srcs/*.c ./srcs/*/*.c)

OBJS		= ${SRCS:.c=.o}

RM		= rm -f

.c.o:
		${CC} -I${INC} -c $< -o ${<:.c=.o} -pthread

$(NAME):	${OBJS}
		make -C libft
		${CC} ${OBJS} ${LIB_NAME} -o ${NAME} -pthread

all:		${NAME}

clean:
		${RM} ${OBJS}
		make clean -C libft

fclean:		clean
		${RM} ${NAME} ${LIB_NAME}

re:		fclean all

.PHONY:		all clean fclean re
