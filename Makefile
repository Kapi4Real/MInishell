
NAME        = minishell
CC          = cc
CFLAGS      = -Wall -Wextra -Werror \
              -I includes \
              -I lib/libft \
              -I lib/get_next_line

# Directories
SRC_DIR     = srcs
GNL_DIR     = lib/get_next_line
LIBFT_DIR   = lib/libft

# Sources
SRCS        = $(wildcard $(SRC_DIR)/*.c) \
              $(wildcard $(SRC_DIR)/builtins/*.c) \
              $(wildcard $(SRC_DIR)/env/*.c) \
              $(wildcard $(SRC_DIR)/exec/*.c) \
              $(wildcard $(SRC_DIR)/parsing/*.c) \
              $(wildcard $(GNL_DIR)/*.c)

OBJS        = $(SRCS:.c=.o)
LIBFT       = $(LIBFT_DIR)/libft.a

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Generic rule for building object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all
