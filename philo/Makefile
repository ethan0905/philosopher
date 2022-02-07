# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: esafar <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/06 17:04:03 by esafar            #+#    #+#              #
#    Updated: 2022/02/07 14:29:14 by esafar           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = ./srcs/philo.c \
		./srcs/init_philo.c \
		./srcs/routine.c \
		./srcs/routine_norm.c \
		./srcs/parsing.c \
		./srcs/start_simulation.c \
		./srcs/time_functions.c \
		./srcs/print.c \
		./srcs/forks.c \
		./srcs/end_simulation.c \
		./srcs/utils/ft_strlen.c \
		./srcs/utils/ft_atoi.c \
		./srcs/utils/ft_isdigit.c \

GCC = cc
FLAGS = -g -pthread -Wextra -Wall -Werror -fsanitize=thread
OBJS = ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${OBJS}
	${GCC} ${FLAGS} ${OBJS} -I includes -o ${NAME}

clean:
	rm -f ${OBJS}

fclean:
	rm -f ${OBJS} ${NAME}

re:	fclean all
