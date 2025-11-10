/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 12:58:31 by imirzaev          #+#    #+#             */
/*   Updated: 2025/10/17 00:22:52 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Définitions ANSI
# define RED     "\x1b[31m"
# define GREEN   "\x1b[32m"
# define YELLOW  "\x1b[33m"
# define BLUE    "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN    "\x1b[36m"
# define RESET   "\x1b[0m"

# include "Libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/time.h>
# include <stdbool.h>
# include <curses.h>
# include <term.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <errno.h>
# include <ctype.h>

//tokenizer
typedef enum TknType
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_OUT_APPEND,
	TOKEN_REDIR_IN,
	TOKEN_HEREDOC,
	TOKEN_FD_REDIR,
	TOKEN_EOF
}	t_TknType;

typedef enum QtType
{
	QUOTE_NONE,
	QUOTE_SINGLE,
	QUOTE_DOUBLE
}	t_QtType;

typedef struct s_wordpart
{
	char				*text;
	t_QtType			quote;
	struct s_wordpart	*next;
}	t_wordpart;

typedef struct Token
{
	t_TknType		type;
	char			*text;
	t_wordpart		*parts;
	t_QtType		quote;
	struct Token	*next;
}	t_Token;

typedef enum NodeType
{
	NODE_COMMAND,
	NODE_PIPELINE,
	NODE_SEQUENCE,
	NODE_REDIR_IN,
	NODE_REDIR_OUT,
	NODE_HEREDOC,
	NODE_REDIR_OUT_APPEND
}	t_NodeType;

typedef struct ASTNode
{
	t_wordpart		**parts;
	int				val;
	int				r_heredoc;
	t_NodeType		type;
	char			*str;
	char			*cmd;
	char			*cmd1;
	char			**argv;
	t_QtType		*quotes;
	struct ASTNode	*left;
	struct ASTNode	*right;
}	t_ASTNode;

//parser.c
typedef struct Parser
{
	t_Token		*current;
	int			val;
	int			argv_count;
}	t_Parser;

//for the pipe : in = write out = read
enum	e_in_out
{
	READ_END,
	WRITE_END
}	;

typedef struct s_heredoc
{
	int		pfd[2];
	char	buf[1024];
	ssize_t	r;
	size_t	len;
}	t_heredoc;

//to get path, get fd, create pipe
typedef struct s_set_fd
{
	int			new_stdin;
	int			new_stdout;
	int			infile_fd;
	int			outfile_fd;
	pid_t		left_pid;
	pid_t		*arrpid;
	bool		is_builtin;
	bool		is_heredoc;
	bool		no_env;
	int			found;
	char		*pathname;
	char		*cmd;
	char		*cmd1;
	int			nbpipes;
	int			nbcmds;
	int			last_exit_status;
	int			prev_pipe[2];
	int			next_pipe[2];
	int			i;
	t_ASTNode	*ast;
}	t_set_fd;

typedef struct s_read
{
	const char	*p;
	char		*out;
	t_QtType	qtype;
	int			unclosed;
	t_wordpart	*parts;
}	t_read;

typedef struct s_expand_ctx
{
	const char	*word;
	t_QtType	qtype;
	char		**env;
	char		*buf;
	size_t		i;
	size_t		start;
	size_t		start_i;
	char		*tmp;
}	t_expand_ctx;

typedef struct s_env_st
{
	char	**env;
	char	**newv;
	char	*dup;
	int		j;
	int		count;
	int		res;
}	t_env_st;

typedef struct s_expand_argv_ctx
{
	char		**argv;
	char		**new_argv;
	char		**split;
	t_QtType	*quotes;
	t_wordpart	**parts;
	char		*expanded;
	int			total;
	int			idx;
	int			i;
	int			j;
	char		**env;
	int			cap;
}	t_expand_argv_ctx;

typedef struct s_expand_argv_input
{
	char		***argv_ptr;
	t_wordpart	***parts_ptr;
	t_QtType	**quotes_ptr;
	char		***newenv;
	t_set_fd	*set_fd;
}	t_expand_argv_input;

typedef struct s_main
{
	t_Token		*tokens;
	t_ASTNode	*ast;
	int			new_last_exit;
	char		*line;
	char		**newenv;
}	t_main;

extern volatile sig_atomic_t	g_sig;

//-----LEXER-----
void		append_wordpart(t_wordpart **list, \
			const char *text, t_QtType quote);
void		free_wordpart_list(t_wordpart *list);
size_t		calculate_parts_length(t_wordpart *parts);
t_Token		*handle_word(const char **p, t_Token *cur);
const char	*read_word(t_Token *token, t_read *ctx);
const char	*consume_quoted_segment(t_Token *token, t_read *ctx);
void		finalize_unquoted_segment(t_Token *token, t_read *ctx);
char		*join_parts_to_string(t_wordpart *parts);
void		copy_parts_into_buffer(t_wordpart *parts, char *s);
t_wordpart	*new_wordpart(const char *text, t_QtType quote);
const char	*read_quoted(t_Token *token, t_read *read, char quote);
void		append_str_lexer(t_Token *token, char **buf, const char *s);
void		append_char_lexer(t_Token *token, char **buf, char c);
void		*safe_malloc(t_Token *token, size_t size);
t_Token		*lexer_process_line(const char *line);
t_Token		*lexer_process_chunk(const char **p, t_Token *cur);
t_Token		*new_token(t_Token *token, t_TknType type, \
			char *text, t_QtType quote);
int			is_operator_char(char c);
void		free_tokens(t_Token *tok);
t_Token		*process_lexer_chunks(const char **p, t_Token *cur, t_Token *head);
t_Token		*lexer_tokenize(const char *line);
t_Token		*handle_operator(const char **p, t_Token *cur);
t_Token		*handle_less(const char **p, t_Token *cur);
t_Token		*handle_greater(const char **p, t_Token *cur);
char		**split_unquoted(const char *s);
char		*consume_quoted_segment_core(t_Token *token, \
			t_read *ctx, t_QtType *qt);
char		*prepare_segment_after_quote(t_read *ctx);

//-----PARSER-----

t_ASTNode	*parser_error(t_ASTNode *node, t_Parser *p);
t_ASTNode	*parse_expression(t_Parser *p);
t_ASTNode	*parse(t_Token *tokens);
t_ASTNode	*parse_primary(t_Parser *p);
t_ASTNode	*parse_sequence(t_Parser *p);
t_ASTNode	*parse_command(t_Parser *p);
t_ASTNode	*parse_pipeline(t_Parser *p);
t_ASTNode	*parse_simple_command(t_Parser *p);
t_ASTNode	*parse_redirections(t_Parser *p, t_ASTNode *cmd);
t_ASTNode	*parse_and_or(t_Parser *p);
t_ASTNode	*parse_one_redirection(t_Parser *p);
t_ASTNode	*parse_single_and_or(t_Parser *p, t_ASTNode *left);

//-----UTILS----

void		free_all(t_ASTNode *ast, t_set_fd *set_fd, char ***newenv);
int			match(t_Parser *p, t_TknType type);
char		*ft_strncpy(char *dest, const char *src, unsigned int n);
void		print_node(t_Token *pargs);
void		print_node_parser(t_Parser *pargs);

//-----UTILS1----

void		ft_puterr(const char *msg);
void		ft_putmsg(const char *msg);
bool		check_is_a_builtin(char **str);
void		for_errors(void);

//-----EXPAND-----

void		expand_ast(t_ASTNode *ast, t_set_fd *set_fd, char ***newenv);
char		*append_char(char **buf, char c);
char		*append_str(char **buf, const char *s);
void		handle_variable_expansion(t_expand_ctx *ctx, t_set_fd *set_fd);
void		process_word_loop(t_expand_ctx *ctx, t_set_fd *set_fd);
char		*expand_word(const char *w, t_QtType qtype, \
			t_set_fd *set_fd, char **nwnv);
char		*expand_from_parts(t_wordpart *parts, \
			t_set_fd *set_fd, char **newenv);
void		expand_dollar_case(t_expand_ctx *ctx, t_set_fd *set_fd);
void		expand_env_variable(t_expand_ctx *ctx);
int			allocate_new_block(char ***arr, int old_cap, \
			int *new_cap, int need);
int			ensure_cap(char ***arr, int *cap, int need);
char		*expand_part(t_wordpart *part, t_set_fd *set_fd, char **envp);
char		**resolve_envp(char ***newenv);
int			add_from_parts_ctx(t_expand_argv_ctx *ctx, t_set_fd *set_fd);
int			handle_unquoted_split_ctx(t_expand_argv_ctx *ctx);
int			process_unquoted_word_ctx(t_expand_argv_ctx *ctx);
int			handle_quoted_word_ctx(t_expand_argv_ctx *ctx);
int			process_regular_word_ctx(t_expand_argv_ctx *ctx, t_set_fd *set_fd);
void		process_each_arg_ctx(t_expand_argv_ctx *ctx, t_set_fd *set_fd);
void		expand_argv(t_expand_argv_input in);

//-----BUILTINS-----

void		is_a_builtin_2(t_ASTNode *node, char ***envp, t_set_fd *set_fd);
void		is_a_builtin(t_ASTNode *node, char ***envp, t_set_fd *set_fd);

//-----ENV-----;

char		**get_newenv(char **newenv, char **env);
void		print_env(char **newenv);
int			ft_env(int argc, char **newenv);

//-----PWD------

int			ft_pwd(t_set_fd *set_fd);
void		update_pwd(char ***envp, const char *cwd);

//-----CD-------
bool		ft_cd(char **argv, char ***envp, t_set_fd *set_fd);

//-----ECHO-----

int			ft_count_args(char **argv);
int			ft_echo(int argc, char **argv, t_set_fd *set_fd);

//-----EXPORT------

int			try_replace_existing_var(t_env_st *st, \
			const char *arg, size_t namelen);
char		**allocate_new_env(t_env_st *st);
int			add_name_without_value(char ***envp, const char *name);
int			handle_export_with_value(char *arg, t_set_fd *set_fd, char ***envp);
int			handle_export_without_value(char *arg, \
			t_set_fd *set_fd, char ***envp);
int			validate_and_prepare_name(char *arg, \
			t_set_fd *set_fd, size_t namelen);
int			is_valid_identifier(const char *s);
int			replace_or_add_var(char ***envp, const char *arg, size_t namelen);
int			ft_export(int argc, char **argv, t_set_fd *set_fd, char ***envp);
size_t		get_name_len_no_equal(const char *name);
int			update_existing_no_value(char **env, \
			const char *name, size_t namelen);
int			append_empty_assignment(char ***envp, const char *name, \
			size_t namelen);

//-----UNSET-------
int			ft_unset(int argc, char **argv, char ***envp);

//-----EXIT--------

int			ft_exit(int argc, char **argv, t_set_fd *set_fd, char ***envp);

//-----EXECUTE-----

bool		close_simple_builtin(t_ASTNode *tmp, \
			t_set_fd *set_fd, char ***newenv);
bool		close_redir(t_ASTNode *tmp, t_set_fd *set_fd, char ***newenv);
bool		execute_ast_cmd(t_ASTNode *tmp, t_set_fd *set_fd, char ***newenv);
bool		execute_ast(t_ASTNode *node, t_set_fd *set_fd, char ***newenv);

//-----EXECUTE1-----

void		close_fd_ast(t_ASTNode *tmp);
bool		exec_pipes(t_ASTNode *tmp, t_set_fd *set_fd, char ***newenv);
bool		exec_node_command(t_ASTNode *tmp, t_set_fd *set_fd, char ***newenv);
int			exec_smple_bltns_and_redir(t_ASTNode *tmp, \
			t_set_fd *set_fd, char ***newenv);

//-----EXECUTE_SINGLE_CMD-----

bool		close_exec_simple(t_set_fd *set_fd, char ***newenv);
void		awaiting_children_single(t_set_fd *set_fd, pid_t pid);
bool		exec_node_command_single(t_ASTNode *tmp, t_set_fd *set_fd, \
			char ***newenv);
bool		exec_single(t_ASTNode *tmp, t_set_fd *set_fd, char ***newenv);

//-----EXECUTE_BUILTINS-----

void		search_builtin(t_ASTNode *tmp, t_set_fd *set_fd);
bool		check_redir(t_ASTNode *tmp, t_set_fd *set_fd);
void		execute_simple_builtin(t_ASTNode *tmp, t_set_fd *set_fd, \
			char ***newenv);

//-----EXECUTE_COMMAND-----

void		awaiting_children(t_set_fd *set_fd, pid_t *pid);
void		fork_fail(t_set_fd *set_fd, char ***newenv);
bool		is_an_absolut_simple(t_ASTNode *node, t_set_fd *set_fd, \
			char ***newenv);
void		exec_builtins(t_ASTNode *node, t_set_fd *set_fd, char ***newenv);
bool		execute_cmd_child_simple(t_ASTNode *node, t_set_fd *set_fd, \
			char ***newenv);

//-----EXECUTE_PIPING1-----

bool		piping1(t_set_fd *set_fd);
bool		piping2(t_set_fd *set_fd);
bool		piping1_and_piping2(t_set_fd *set_fd, char ***newenv);

//-----EXECUTE_CLOSE_FD-----

bool		close_fd(int *fd);
bool		close_pipe(int fd[2]);
void		close_safe(t_set_fd *set_fd, char ***newenv);
bool		close_and_switch_pipe(t_set_fd *set_fd);
void		close_all_pipes(t_set_fd *set_fd);

//------EXECUTE_UTILS------

t_ASTNode	*search_cmds(t_ASTNode *tmp);
char		*cmd_transfert(t_ASTNode *tmp, char *short_path);
char		*check_path(t_ASTNode *node, t_set_fd *set_fd);
bool		get_path(t_set_fd *set_fd, char **newenv);
void		init_execute_child(t_set_fd *set_fd);

//------EXECUTE_UTILS1------

bool		close_node_pipe(t_set_fd *set_fd, char ***newenv);
char		*get_env_value(char **env, const char *name);
void		free_and_exit(t_ASTNode *tmp);
void		kill_command(t_set_fd *set_fd);
bool		exec_simple_without_pipe(t_ASTNode *tmp, \
			t_set_fd *set_fd, char ***newenv);

//-----REDIRECTIONS-----

bool		open_file_redir_in(t_ASTNode *tmp, t_set_fd *set_fd);
bool		open_file_redir_out(t_ASTNode *tmp, t_set_fd *set_fd);
bool		open_file_redir_append(t_ASTNode *tmp, t_set_fd *set_fd);
bool		check_file(t_ASTNode *tmp, t_set_fd *set_fd);

//-----DUP_REDIR-----

bool		close_file(int *infile, int *outfile);
bool		dup_file_redir_in(t_set_fd *set_fd);
bool		dup_file_redir_out(t_set_fd *set_fd);
bool		dup_file_redir_append(t_set_fd *set_fd);

//-----HEREDOCS-----

void		error_msg_heredoc(const char *delim);
bool		write_error(t_heredoc *heredoc);
size_t		read_heredoc(t_heredoc *heredoc);
bool		set_pipe_heredoc(int pfd[2]);
bool		heredoc_to_stdin(t_ASTNode *node, const char *delim, \
			t_set_fd *set_fd);

//-----HEREDOCS1-----

bool		dup_heredoc(t_ASTNode *node, int *pfd, t_set_fd *set_fd);

//-----DUP-----

void		set_pipe(t_set_fd *set_fd, char ***newenv);
bool		dup_stds(int *new_stdin, int *new_stdout, \
			int oldstdin, int oldstdout);
bool		reset_stds(int new_stdin, int new_stdout);
bool		dup_prev_pipe(t_set_fd *set_fd);
bool		dup_next_pipe(t_set_fd *set_fd);

//------AST--------

void		free_partial_argv(char **argv, int count);
char		**create_node_command(t_ASTNode *node, t_Parser *p);
char		**create_node_redir(t_ASTNode *redir, t_Parser *p);
t_ASTNode	*new_node_parser(t_NodeType type, t_Parser *p);

//------AST_INIT--------

void		init_create_node_cmd(t_ASTNode *node);
void		init_new_node(t_ASTNode *node, t_Parser *p);
void		init_new_node1(t_ASTNode *node);

//------AST_UTILS--------

void		print_depth_first_search_recursiv(t_ASTNode *node, int depth);
void		free_ast(t_ASTNode *node);
bool		is_a_redir(t_NodeType type);
// void		free_ast_recursive(ASTNode *node);

//-----SYNTAX_ERROR-----

bool		syntax_error(t_set_fd *set_fd, t_Token *parg);

//-----SYNTAX_ERROR1-----

void		exec_error_handler(t_set_fd *set_fd, char *cmd, char ***newenv);

//-----SYNTAX_ERROR_UTILS-----

bool		is_logic(t_Token *t);
bool		is_redirection(t_TknType t);
void		ft_puterr_token(char *msg, char *tok);
void		ft_puterr_cmd_not_fnd(void);
void		ft_puterr_cmd_not_fnd_tok(char *tok);

//-----SYNTAX_ERROR_UTILS1-----

bool		is_pipe(t_TknType t);
char		*display_tok_text(t_Token *t);
int			is_directory(const char *path);

//-----ERROR_REDIR-----

void		msg_error_open_file(t_set_fd *set_fd, char *cmd);

//------SIGNALS-----

void		setup_signals(void);
void		setup_signals_fork(void);
void		setup_signals_heredoc(void);
void		check_g_sig(t_set_fd *set_fd);
void		install_heredoc_signals(void);

//------SIGNALS1-----

void		sigint_handler(int sig);
void		sigint_handler_heredoc(int sig);

//-----FREE-----

void		free_set_fd(t_set_fd *set_fd);
void		free_exec(t_set_fd *set_fd, char ***newenv);
void		free_builtins(t_set_fd *set_fd, char ***newenv);
void		free_end_loop(t_set_fd *set_fd, char *line, t_ASTNode **ast);

#endif 
