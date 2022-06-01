NAME=            libft.a
TEST_FILE=        Test.c
FLAGS=            -Wall -Werror -Wextra
CC=                cc
SRC_FILES = ft_isalnum.c \
			ft_isdigit.c \
			ft_memmove.c \
			ft_strlen.c \
			ft_atoi.c \
			ft_isalpha.c \
			ft_isprint.c \
			ft_memset.c \
			ft_strncmp.c \
			ft_bzero.c \
			ft_isascii.c \
			ft_memcpy.c \
			ft_strlcpy.c \
			ft_strnstr.c \
			ft_strchr.c \
			ft_strrchr.c \
			ft_strlcat.c \
			ft_memcmp.c \
			ft_toupper.c \
			ft_tolower.c \
			ft_calloc.c \
			ft_strdup.c \
			ft_memchr.c \
			ft_strtrim.c \
			ft_itoa.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putnbr_fd.c \
			ft_putendl_fd.c \
			ft_substr.c \
			ft_strjoin.c \
			ft_strmapi.c \
			ft_split.c \
			ft_striteri.c \

SRC_FILES_BONUS = ft_lstnew_bonus.c \
				ft_lstadd_front_bonus.c \
				ft_lstlast_bonus.c \
				ft_lstadd_back_bonus.c \
				ft_lstlast_bonus.c \
				ft_lstsize_bonus.c \
				ft_lstdelone_bonus.c \
				ft_lstclear_bonus.c \
				ft_lstiter_bonus.c

OBJ_FILES=			$(SRC_FILES:.c=.o)
OBJ_FILES_BONUS=	$(SRC_FILES_BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ_FILES)
	ar rcs $(NAME) $(OBJ_FILES) 

%.o: %.c
	$(CC) $(FLAGS) -c $<

clean:
	find . -name "*.o" -delete

fclean: clean
	rm -f $(NAME)

re: fclean all

Bonus:  $(OBJ_FILES_BONUS)
	ar rcs $(NAME) $(OBJ_FILES_BONUS) 

