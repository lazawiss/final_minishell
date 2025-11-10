CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -ILibft
LDFLAGS = -lreadline -lncurses

MAIN = main.c \
		utils.c \
		utils1.c \
		signals.c \
		signals1.c \
		free.c 

AST = \
		ast/ast.c \
		ast/ast_init.c \
		ast/ast_utils.c 

BUILTINS = \
		builtins/env.c \
		builtins/builtins.c \
		builtins/echo.c \
		builtins/ft_pwd.c \
		builtins/ft_cd.c \
		builtins/ft_unset.c \
		builtins/export.c \
		builtins/export_utils.c \
		builtins/export_utils2.c \
		builtins/exit.c 

LEXER = \
		lexer/lexer.c \
		lexer/lexer2.c \
		lexer/lexer3.c \
		lexer/lexer_utils.c \
		lexer/lexer_utils_2.c \
		lexer/lexer_tokenizer.c

PARSER = \
		parser/parser.c \
		parser/parser_utils.c \
		parser/parser_utils_2.c

EXPAND = \
		expand/expand.c \
		expand/expand_word.c \
		expand/expand_word2.c \
		expand/expand_argv.c \
		expand/expand_argv2.c \
		expand/expand_argv3.c \
		expand/split_unquoted.c

REDIRECTIONS = \
		redirections/redirections.c \
		redirections/dup_redir.c \
		redirections/heredocs.c \
		redirections/heredocs1.c

EXEC = \
		exec/execute.c \
		exec/execute1.c \
		exec/execute_single_cmd.c \
		exec/execute_builtins.c \
		exec/execute_command.c \
		exec/execute_piping1.c \
		exec/execute_utils.c \
		exec/execute_utils1.c \
		exec/dup.c \
		exec/execute_close_fd.c 

ERROR = \
		error/syntax_error.c \
		error/error_redir.c \
		error/syntax_error1.c \
		error/syntax_error_utils.c \
		error/syntax_error_utils1.c

LIB = Libft/libft.a

SRCS = $(MAIN) $(AST) $(BUILTINS) $(REDIRECTIONS) $(EXEC) $(LEXER) $(EXPAND) $(PARSER) $(ERROR)
OBJS = $(SRCS:.c=.o)

NAME = minishell

all: $(NAME)

$(NAME): $(OBJS) $(LIB)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
	
$(LIB): 
	$(MAKE) -C Libft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(LIB)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

