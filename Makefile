NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC_FILES = \
	libft/convert/ft_atoi.c \
	libft/convert/ft_atol.c \
	libft/convert/ft_itoa.c \
	libft/convert/ft_tolower.c \
	libft/convert/ft_toupper.c \
	libft/gnl/get_next_line.c \
	libft/is/ft_isalnum.c \
	libft/is/ft_isalpha.c \
	libft/is/ft_isascii.c \
	libft/is/ft_isdigit.c \
	libft/is/ft_isnegative.c \
	libft/is/ft_isprint.c \
	libft/is/ft_isspace.c \
	libft/mem/ft_bzero.c \
	libft/mem/ft_calloc.c \
	libft/mem/ft_memchr.c \
	libft/mem/ft_memcmp.c \
	libft/mem/ft_memcpy.c \
	libft/mem/ft_memmove.c \
	libft/mem/ft_memset.c \
	libft/print/ft_print_char.c \
	libft/print/ft_print_hexaptr.c \
	libft/print/ft_print_nbr.c \
	libft/print/ft_print_str.c \
	libft/printf/ft_printf.c \
	libft/put/ft_put_unsigned.c \
	libft/put/ft_putchar_fd.c \
	libft/put/ft_putendl_fd.c \
	libft/put/ft_puthexa_lower.c \
	libft/put/ft_puthexa_ptr.c \
	libft/put/ft_puthexa_upper.c \
	libft/put/ft_putnbr_fd.c \
	libft/put/ft_putstr_fd.c \
	libft/str/ft_split.c \
	libft/str/ft_strchr.c \
	libft/str/ft_strdup.c \
	libft/str/ft_striteri.c \
	libft/str/ft_strjoin.c \
	libft/str/ft_strlcat.c \
	libft/str/ft_strlcpy.c \
	libft/str/ft_strlen.c \
	libft/str/ft_strmapi.c \
	libft/str/ft_strcmp.c \
	libft/str/ft_strncmp.c \
	libft/str/ft_strnstr.c \
	libft/str/ft_strrchr.c \
	libft/str/ft_strtrim.c \
	libft/str/ft_substr.c \
	libft/struct/ft_addback.c \
	libft/free/free_all.c \
	libft/free/free_array.c \
	libft/free/free_shell.c \
	libft/free/free_redir_struct.c \
	libft/free/free_cmd.c \
	libft/free/free_tokens.c \
	libft/free/free_envp_struct.c \
	libft/print/ft_print_tab.c \
	libft/shell/ft_cmd.c \
	parsing/parsing.c \
	parsing/parser.c \
	parsing/expander_utils.c \
	parsing/expander.c \
	parsing/parser_utils.c \
	parsing/parser_utils2.c \
	parsing/tokenizer_utils.c \
	parsing/tokenizer.c \
	parsing/tokenizer_helpers.c \
	parsing/token_filter.c \
	exec/exec.c \
	exec/external_cmd.c \
	exec/path_utils.c \
	exec/path_utils2.c \
	exec/exec_errors.c \
	builtins/builtins.c \
	builtins/builtin_echo.c \
	builtins/builtin_env.c \
	builtins/builtin_exit.c \
	builtins/builtin_pwd.c \
	builtins/builtin_cd.c \
	builtins/builtin_export.c \
	builtins/builtin_unset.c \
	exec/env_utils.c \
	exec/env_utils2.c \
	exec/pipe_utils.c \
	exec/pipe_execution.c \
	exec/redirections.c \
	exec/here_doc.c \
	exec/here_doc2.c \
	signal_handler.c \
	signal_setup.c \
	init_shell.c \
	main.c

OBJ_DIR = obj

OBJ = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m
CLEAR_LINE = \033[2K\r

all: $(NAME)

$(NAME): $(OBJ)
	@printf "$(CLEAR_LINE)$(GREEN)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) -o $@ -lreadline
	@printf "$(CLEAR_LINE)$(GREEN)$(NAME) compiled successfully!$(RESET)\n"

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@printf "$(CLEAR_LINE)$(GREEN)Compiling $<...$(RESET)"
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@printf "$(RED)Object files cleaned!$(RESET)\n"

fclean: clean
	@rm -f $(NAME)
	@printf "$(RED)Executable $(NAME) removed!$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re
