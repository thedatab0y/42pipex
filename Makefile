NAME= pipex.a

CC = gcc
CFLAGS= -Wall -Werror -Wextra -g
HEADER= pipex.h
RM= rm -rf
NAME = pipex
#DEBUG = -fsanitize=address


FILES=	func/main.c \
		func/gp_exec.c \
		utils/ft_split.c \
		utils/ft_strjoin.c \
		utils/ft_strncmp.c

O_FILES= $(FILES:%.c=%.o)

all: $(NAME)

$(NAME): $(O_FILES)
	$(CC) $(CFLAGS) $(DEBUG) $(O_FILES) $(LIBFT) -o $(NAME)

clean:
	$(RM) $(O_FILES)
	
fclean: clean
	$(RM) $(NAME)
	
re: fclean all

.PHONY: all clean fclean re