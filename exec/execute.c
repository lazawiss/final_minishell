/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 22:19:09 by lzannis           #+#    #+#             */
/*   Updated: 2025/10/16 21:54:14 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
// ls | cat -e | cat -e | cat -e | cat -e

void	init_execute_ast(t_ASTNode *node, t_set_fd *set_fd)
{
	set_fd->ast = node;
	set_fd->infile_fd = -1;
	set_fd->outfile_fd = -1;
}

bool	close_simple_builtin(t_ASTNode *tmp, t_set_fd *set_fd, char ***newenv)
{
	if (!close_file(&set_fd->infile_fd, &set_fd->outfile_fd))
	{
		close_safe(set_fd, newenv);
		return (false);
	}
	if (!reset_stds(set_fd->new_stdin, set_fd->new_stdout))
	{
		free_ast(tmp);
		return (false);
	}
	return (true);
}

bool	close_redir(t_ASTNode *tmp, t_set_fd *set_fd, char ***newenv)
{
	close_fd_ast(tmp);
	if (!close_file(&set_fd->infile_fd, &set_fd->outfile_fd))
	{
		close_safe(set_fd, newenv);
		return (false);
	}
	close_fd(&set_fd->new_stdin);
	close_fd(&set_fd->new_stdout);
	return (true);
}

bool	execute_ast_cmd(t_ASTNode *tmp, t_set_fd *set_fd, char ***newenv)
{
	if (set_fd->is_builtin == false && \
	set_fd->found == 1 && set_fd->nbpipes == 0)
	{
		return (exec_simple_without_pipe(tmp, set_fd, newenv));
	}
	else if (set_fd->found != 0)
	{
		init_execute_child(set_fd);
		if (!exec_pipes(tmp, set_fd, newenv))
		{
			close_safe(set_fd, newenv);
			return (false);
		}
		if (!close_node_pipe(set_fd, newenv))
			return (false);
		close_fd_ast(tmp);
	}
	if (!reset_stds(set_fd->new_stdin, set_fd->new_stdout))
		return (free_ast(tmp), false);
	return (true);
}

bool	execute_ast(t_ASTNode *node, t_set_fd *set_fd, char ***newenv)
{
	t_ASTNode	*tmp;
	int			builtins;

	tmp = node;
	init_execute_ast(node, set_fd);
	if (!get_path(set_fd, *newenv))
		return (false);
	if (!dup_stds(&set_fd->new_stdin, &set_fd->new_stdout, \
	STDIN_FILENO, STDOUT_FILENO))
		return (free_ast(tmp), false);
	search_builtin(tmp, set_fd);
	builtins = exec_smple_bltns_and_redir(tmp, set_fd, newenv);
	if (builtins == 0)
		return (false);
	else if (builtins == 1)
		return (true);
	set_fd->nbcmds = set_fd->found;
	if (!execute_ast_cmd(tmp, set_fd, newenv))
		return (false);
	return (true);
}
