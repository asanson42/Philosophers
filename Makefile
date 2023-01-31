CC		= gcc -g

CFLAGS		= -Wall -Wextra -Werror

NAME		= philo

INC		= ./inc/

SRCS		= $(wildcard ./srcs/*.c ./srcs/*/*.c)

OBJS		= ${SRCS:.c=.o}

RM		= rm -f

.c.o:
		${CC} ${CFLAGS} -I${INC} -c $< -o ${<:.c=.o} -pthread

$(NAME):	${OBJS}
		${CC} ${CFLAGS} ${OBJS} -o ${NAME} -pthread

all:		${NAME}

clean:	
		${RM} ${OBJS}

fclean:		clean
		${RM} ${NAME}

re:		fclean all

.PHONY:		all clean fclean re
