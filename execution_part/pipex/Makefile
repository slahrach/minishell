# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/14 16:41:34 by iouardi           #+#    #+#              #
#    Updated: 2022/04/11 00:59:12 by iouardi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=            pipex
NAME_BONUS=            pipex_bonus
TEST_FILE=        Test.c
FLAGS=            -Wall -Werror -Wextra
CC=                cc
SRC_FILES = mandatory/pipex.c \
			mandatory/find_path.c \
			mandatory/execute_cmds.c
SRC_FILES_BONUS = bonus/pipex_bonus.c \
				bonus/find_path_bonus.c \
				bonus/get_next_line.c \
				bonus/get_next_line_utils.c \
				bonus/execute_cmd_bonus.c \
				bonus/here_doc_bonus.c
				
OBJ_FILES=			$(SRC_FILES:.c=.o)
OBJ_FILES_BONUS=	$(SRC_FILES_BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ_FILES)
	@make -C mandatory/libft
	@cp mandatory/libft/libft.a ./
	$(CC) $(OBJ_FILES) -o $(NAME) libft.a
%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	find . -name "*.o" -delete
	find . -name "*.a" -delete

fclean: clean
	rm -f $(NAME) outfile

re: fclean all

bonus: $(OBJ_FILES_BONUS)
	@make -C mandatory/libft
	@cp mandatory/libft/libft.a ./
	$(CC) $(FLAGS) $(OBJ_FILES_BONUS) -o $(NAME) libft.a

.PHONY:
	all clean fclean re bonus