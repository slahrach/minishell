# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/20 05:51:28 by slahrach          #+#    #+#              #
#    Updated: 2022/04/28 21:14:07 by slahrach         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = main.c utils.c error.c parsing.c

CFLAGS = -Wall -Wextra -Werror


LIB = libft/libft.a

OBJS = ${SRCS:.c=.o}

${NAME} : ${OBJS}
		make -C libft
		gcc ${CFLAGS} ${OBJS} ${LIB} -o ${NAME} -lreadline -L /Users/slahrach/.brew/opt/readline/lib -I/Users/slahrach/.brew/opt/readline/include

all : ${NAME}

clean :
	make clean -C libft
	rm -rf ${OBJS}

fclean : clean
	make fclean -C libft
	rm -rf ${NAME}

re : fclean all

%.o : %.c
	${CC} ${CFLAGS} -I/Users/slahrach/.brew/opt/readline/include -c $<

.PHONY: clean all fclean re