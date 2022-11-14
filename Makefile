CC = gcc

NAME= pipex

CFLAGS= -Wall -Werror -Wextra

HEADER= pipex.h

RM= rm -rf

NAME = pipex

FILES=	func/main.c \
		func/gp_exec.c \
		utils/ft_split.c \
		utils/ft_strjoin.c \
		utils/ft_strncpm.c

OBJ= $(FILES:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)

	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)
	
fclean: clean
	$(RM) $(NAME)
	
re: fclean all

.PHONY: all clean fclean re
    