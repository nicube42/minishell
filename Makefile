RED = \033[0;31m
NOCOLOR = \033[0m
GREEN = \033[0;32m
RED = \033[1;31m

PATH_SRC =			./srcs/
PATH_LIBFT =		./libft_printf/
PATH_OBJS =			./objs/

LIBFT = $(PATH_LIBFT)libftprintf.a
NAME = minishell

FILES = $(PATH_SRC)parsing.c $(PATH_SRC)type_detector.c $(PATH_SRC)lexer.c $(PATH_SRC)lexer_utils.c $(PATH_SRC)token_creator.c $(PATH_SRC)cmd_token.c $(PATH_SRC)dollar_token.c $(PATH_SRC)redir_token.c
OBJS = $(patsubst $(PATH_SRC)%.c, $(PATH_OBJS)%.o, $(FILES))

CC = clang
CFLAGS = -Wextra -Werror -Wall
RM = rm -rf

all: logo $(NAME)

logo :
			@tput setaf 2; cat ascii_art/42minishell; tput setaf default

$(NAME): $(OBJS)
	@$(MAKE) -C $(PATH_LIBFT)
	@echo "Assembling $(NAME)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "${GREEN}✓${NOCOLOR}"
	@echo "$(GREEN)Compilation is done$(NOCOLOR)"

$(PATH_OBJS)%.o:	$(PATH_SRC)%.c
	@echo "Compiling $^: "
	@mkdir -p $(PATH_OBJS)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "${GREEN}✓${NOCOLOR}"

clean:
	@echo "${RED}Cleaning objects in minishell: ${NOCOLOR}"
	@$(RM) $(PATH_OBJS)
	@echo "${GREEN}✓${NOCOLOR}"

fclean: clean
	@make fclean -C $(PATH_LIBFT)
	@echo "${RED}Cleaning all in minishell: ${NOCOLOR}"
	@$(RM) $(NAME)
	@echo "${GREEN}✓${NOCOLOR}"

re: fclean all

norme: 
	norminette $(PATH_SRC) $(PATH_LIBFT) ./includes

.PHONY: re all fclean clean norme