NAME = pipex
CC = cc
FLAGS = -Wall -Werror -Wextra

LIBFT = libft.a
SRC = 	src/main.c \
		src/ft_exit.c \
		src/ft_parsing.c \
		src/ft_pipex.c \
		src/ft_check_path.c \
		\

all: $(NAME)

$(NAME): $(LIBFT)
	@$(CC) $(FLAGS) $(SRC) -Iinclude -Ilibft/include -Llibft -lft -o $(NAME)

$(LIBFT):
	@make --no-print-directory -C libft

clean:
	@make --no-print-directory clean -C libft 

fclean: clean
	@make --no-print-directory fclean -C libft
	@rm -f $(NAME)

re: fclean all
	@clear
	@valgrind ./pipex in "/bin/ls -l" "cat" outfile
