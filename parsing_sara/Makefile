# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/20 05:51:28 by slahrach          #+#    #+#              #
#    Updated: 2022/05/24 17:25:43 by iouardi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = main.c \
	utils.c \
	error.c \
	parsing.c \
	expansion.c \
	builtins.c \
	devide.c \
	envr.c \
	list_utils.c \
	exec.c

CFLAGS = -Wall -Wextra -Werror


LIB = libft/libft.a

OBJS = ${SRCS:.c=.o}

${NAME} : ${OBJS}
		make -C libft
		gcc ${CFLAGS} ${OBJS} ${LIB} -o ${NAME} -lreadline -L /Users/iouardi/.brew/opt/readline/lib -I/Users/iouardi/.brew/opt/readline/include -fsanitize=address -g

all : ${NAME}

clean :
	make clean -C libft
	rm -rf ${OBJS}

fclean : clean
	make fclean -C libft
	rm -rf ${NAME}

re : fclean all

%.o : %.c
	${CC} ${CFLAGS} -I /Users/iouardi/.brew/opt/readline/include -c $<

.PHONY: clean all fclean re