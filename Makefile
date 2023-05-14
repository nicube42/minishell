NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC = main.c utils.c lexer/cmd_token.c  lexer/dollar_token.c  lexer/lexer.c  lexer/lexer_utils.c  lexer/parsing.c  lexer/redir_token.c  lexer/token_creator.c  lexer/type_detector.c lexer/check_syntax.c lexer/parsing_utils.c execution/execute.c
DIRS	= lexer/ parsing/ execution/


OBJ_DIR = $(addprefix obj/, $(DIRS))
OBJS = $(addprefix obj/, $(SRC:.c=.o))
SRCS = $(addprefix src/, $(SRC))

LIBFT = libft.a

all: create_dirs $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C ./libft

create_dirs:
	mkdir -p obj/
	mkdir -p $(OBJ_DIR)

$(NAME): $(OBJS)
	$(CC)  $(CFLAGS) $(OBJS) -o $(NAME) -lreadline -Llibft/ -lftprintf

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $< -I ./includes

clean:
	rm -rf obj/
	$(MAKE) -C libft/ clean

fclean:
	rm -rf obj/
	rm -f $(NAME)
	$(MAKE) -C libft/ fclean

re: fclean all

fast:
	$(MAKE) -j -C ./libft
	$(MAKE) -j$(nproc)

.PHONY: all create_dirs clean fclean re fast

