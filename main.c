/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 20:13:11 by lzannis           #+#    #+#             */
/*   Updated: 2025/10/16 20:38:00 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig;

void	set_up_main(t_main *main, t_set_fd *set_fd)
{
	setup_signals();
	main->new_last_exit = set_fd->last_exit_status;
	ft_memset(set_fd, 0, sizeof(t_set_fd));
	set_fd->last_exit_status = main->new_last_exit;
	main->line = readline("minish-elles$: ");
	if (!main->line)
	{
		free(main->line);
		free_all(main->ast, set_fd, &main->newenv);
		exit(EXIT_SUCCESS);
	}
	if (main->line && *main->line)
		add_history(main->line);
	check_g_sig(set_fd);
	g_sig = 0;
}

void	error_token(t_set_fd *set_fd, t_Token *tokens, char *line)
{
	if (!tokens)
		ft_puterr_cmd_not_fnd_tok(line);
	else if (!tokens->text)
		ft_puterr_cmd_not_fnd();
	free(line);
	set_fd->last_exit_status = 127;
	free_tokens(tokens);
}

bool	set_ast_and_execute(t_main *main, t_set_fd *set_fd)
{
	if (!syntax_error(set_fd, main->tokens))
	{
		main->ast = parse(main->tokens);
		free_tokens(main->tokens);
		if (main->ast)
		{
			expand_ast(main->ast, set_fd, &main->newenv);
			if (!execute_ast(main->ast, set_fd, &main->newenv))
				return (false);
		}
	}
	return (true);
}

void	init_main(t_main *main, t_set_fd *set_fd, char **env)
{
	main->line = NULL;
	main->ast = NULL;
	main->tokens = NULL;
	main->new_last_exit = 0;
	main->newenv = get_newenv(main->newenv, env);
	set_fd->last_exit_status = 0;
}

int	main(int ac, char **av, char **env)
{
	t_main		main;
	t_set_fd	set_fd;

	(void)av;
	if (ac != 1)
		for_errors();
	init_main(&main, &set_fd, env);
	while (1)
	{
		set_up_main(&main, &set_fd);
		if (*main.line == '\0')
		{
			free(main.line);
			continue ;
		}
		main.tokens = lexer_tokenize(main.line);
		if (!main.tokens || !main.tokens->text)
		{
			error_token(&set_fd, main.tokens, main.line);
			continue ;
		}
		set_ast_and_execute(&main, &set_fd);
		free_end_loop(&set_fd, main.line, &main.ast);
	}
	return (0);
}
