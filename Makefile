CC = cc
CFLAGS = -Wall -Wextra -Werror

SOURCES =	pipex.c \
			parsing.c \
			free_and_error.c \
			fork.c \
			p_split.c \
			p_split_utils.c

NAME = pipex
HEADER = pipex.h
BONUS_NAME = checker

LIBFT_DIR = libft
LDFLAGS = -L$(LIBFT_DIR) -lft

LIBFT_MARKER = .libft

$(LIBFT_MARKER):
	@$(MAKE) -C $(LIBFT_DIR) > /dev/null
	@echo "Built libft"
	touch $(LIBFT_MARKER) > /dev/null

$(NAME): $(LIBFT_MARKER)
	$(CC) -g $(CFLAGS) $(SOURCES) $(LDFLAGS) -o $(NAME)
	@echo "Built pipex"

all: $(NAME)

re: fclean all

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean > /dev/null
	@echo "Removed object files"

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean > /dev/null
	rm -f $(LIBFT_MARKER)
	rm -f $(NAME)
	@echo "Removed executables"

.PHONY: all re clean fclean bonus
