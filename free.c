/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 20:58:05 by lzannis           #+#    #+#             */
/*   Updated: 2025/10/13 18:02:06 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_set_fd(t_set_fd *set_fd)
{
	if (set_fd->arrpid)
		free(set_fd->arrpid);
	if (set_fd->cmd1)
		free(set_fd->cmd1);
	if (set_fd->pathname)
		free(set_fd->pathname);
	if (set_fd->ast)
		free_ast(set_fd->ast);
}

void	free_exec(t_set_fd *set_fd, char ***newenv)
{
	rl_clear_history();
	if (*newenv)
		ft_free(*newenv);
	if (set_fd)
		free_set_fd(set_fd);
	return ;
}

void	free_builtins(t_set_fd *set_fd, char ***newenv)
{
	close_fd(&set_fd->new_stdin);
	close_fd(&set_fd->new_stdout);
	rl_clear_history();
	if (*newenv)
		ft_free(*newenv);
	if (set_fd)
		free_set_fd(set_fd);
}

void	free_end_loop(t_set_fd *set_fd, char *line, t_ASTNode **ast)
{
	kill_command(set_fd);
	free(line);
	*ast = NULL;
}
