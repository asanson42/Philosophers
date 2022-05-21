# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asanson <asanson@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/19 02:36:15 by asanson           #+#    #+#              #
#    Updated: 2022/05/19 02:36:18 by asanson          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= $(wildcard ./*.c)

OBJS		= ${SRCS:.c=.o}

NAME		= libft.a

CC		= gcc

CFLAGS	 	= -Wall -Werror -Wextra -I.

RM		= rm -f

.c.o:	
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS}
		ar -rcs ${NAME} ${OBJS}

all:		${NAME}

clean:	
		${RM} ${OBJS}

fclean:		clean
		${RM} ${NAME}

re:		fclean all

.PHONY:		all clean fclean re
