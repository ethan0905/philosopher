# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: esafar <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/06 17:04:03 by esafar            #+#    #+#              #
#    Updated: 2022/02/08 17:15:28 by esafar           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = ./philo.c \
		./init_philo.c \
		./routine.c \
		./routine_norm.c \
		./parsing.c \
		./start_simulation.c \
		./time_functions.c \
		./print.c \
		./forks.c \
		./end_simulation.c \
		./ft_strlen.c \
		./ft_atoi.c \
		./ft_isdigit.c \

GCC = cc
FLAGS = -g -pthread -Wextra -Wall -Werror #-fsanitize=thread
OBJS = ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${OBJS}
	${GCC} ${FLAGS} ${OBJS} -I includes -o ${NAME}

clean:
	rm -f ${OBJS}

fclean:
	rm -f ${OBJS} ${NAME}

re:	fclean all

%.o: %.c ${INCL}
	${GCC} ${FLAGS} -c $< -o ${<:.c=.o}

.PHONY: all clean fclean re