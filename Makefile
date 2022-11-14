NAME = pipex.a

FILES=	files/pipex.c \
		files/execute.c \
		utils/ft_split.c \
		utils/ft_strjoin.c \
		utils/ft_strncmp.c

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

OBJ = $(FILES:.c=.o)

%.o : %.c
	gcc -o $@ -c $< $(CFLAGS)

$(NAME): $(OBJ)
	gcc $(OBJ) $(CFLAGS) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
