# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asajid <asajid@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/16 18:11:56 by asajid            #+#    #+#              #
#    Updated: 2023/10/19 17:26:56 by asajid           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = main.c init.c phil_threads.c \
	phil_actions.c time.c error_check.c \
	phil_utils.c

OBJS = ${SRCS:.c=.o}

CC = gcc -pthread

CFLAGS = -Wall -Wextra -Werror

RM = rm -rf


all: ${NAME}
${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME}


clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
