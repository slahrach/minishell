# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/20 05:51:28 by slahrach          #+#    #+#              #
#    Updated: 2022/07/20 01:34:37 by iouardi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = main.c \
	utils.c \
	error.c \
	tokenizer.c \
	expansion.c \
	parser.c \
	envr.c \
	list_utils.c \
	exec1.c \
	exec2.c \
	exec3.c \
	cd_command.c \
	export.c \
	export_utils.c \
	find_cmd_path.c \
	execute_commands.c \
	here_doc.c \
	utils2.c \
	utils1.c \
	unset_node.c \
	check_pipes_and_redirections.c \

CFLAGS = -Wall -Wextra -Werror


LIB = libft.a

OBJS = ${SRCS:.c=.o}

${NAME} : ${OBJS}
		@make -C libft
		@cp libft/libft.a ./
		gcc -g $(CFLAGS) ${OBJS} ${LIB} -o ${NAME} -lreadline -L /Users/iouardi/.brew/opt/readline/lib -I /Users/iouardi/.brew/opt/readline/include

all : ${NAME}

clean :
	make clean -C libft
	rm -rf ${OBJS}

fclean : clean
	make fclean -C libft
	rm -rf ${NAME}
	rm -rf ${LIB}

re : fclean all

%.o : %.c
	${CC} $(CFLAGS) -g -I /Users/iouardi/.brew/opt/readline/include -c $<

.PHONY: clean all fclean re
