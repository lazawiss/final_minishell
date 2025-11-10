/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 18:43:11 by lzannis           #+#    #+#             */
/*   Updated: 2025/10/17 00:38:44 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	exec_node_command(t_ASTNode *tmp, t_set_fd *set_fd, char ***newenv)
{
	g_sig = 1;
	set_pipe(set_fd, newenv);
	set_fd->arrpid[set_fd->i] = fork();
	if (set_fd->arrpid[set_fd->i] < 0)
		fork_fail(set_fd, newenv);
	else if (set_fd->arrpid[set_fd->i] == 0)
	{
		if (!execute_cmd_child_simple(tmp, set_fd, newenv))
			return (false);
	}
	set_fd->i++;
	if (!close_and_switch_pipe(set_fd))
	{
		close_safe(set_fd, newenv);
		return (false);
	}
	if (!close_file(&set_fd->infile_fd, &set_fd->outfile_fd))
	{
		close_safe(set_fd, newenv);
		return (false);
	}
	close_all_pipes(set_fd);
	return (true);
}

bool	exec_pipes(t_ASTNode *tmp, t_set_fd *set_fd, char ***newenv)
{
	if (is_a_redir(tmp->type))
	{
		if (!check_file(tmp, set_fd))
			return (false);
		if (tmp->left)
			exec_pipes(tmp->left, set_fd, newenv);
		if (tmp->right)
			exec_pipes(tmp->right, set_fd, newenv);
	}
	if (tmp->type == NODE_COMMAND)
	{
		if (!exec_node_command(tmp, set_fd, newenv))
			return (false);
	}
	if (tmp->type == NODE_PIPELINE)
	{
		if (tmp->left)
			exec_pipes(tmp->left, set_fd, newenv);
		if (tmp->right)
			exec_pipes(tmp->right, set_fd, newenv);
	}
	return (true);
}

void	close_fd_ast(t_ASTNode *tmp)
{
	if (tmp->r_heredoc > 0)
	{
		if (!close_fd(&tmp->r_heredoc))
			return ;
	}
	if (tmp->left)
		close_fd_ast(tmp->left);
	if (tmp->right)
		close_fd_ast(tmp->right);
}

int	simple_redir_exec(t_ASTNode *tmp, t_set_fd *set_fd, char ***newenv)
{
	if (!check_redir(tmp, set_fd))
	{
		if (!close_redir(tmp, set_fd, newenv))
			return (0);
		return (0);
	}
	if (!close_redir(tmp, set_fd, newenv))
		return (0);
	return (1);
}

int	exec_smple_bltns_and_redir(t_ASTNode *tmp, t_set_fd *set_fd, char ***newenv)
{
	if (g_sig == 130)
	{
		if (!reset_stds(set_fd->new_stdin, set_fd->new_stdout))
			return (free_ast(tmp), 0);
		return (1);
	}
	if (set_fd->is_builtin == true && set_fd->found == 1)
	{
		execute_simple_builtin(tmp, set_fd, newenv);
		if (!close_simple_builtin(tmp, set_fd, newenv))
			return (0);
		return (1);
	}
	if (set_fd->is_builtin == false && set_fd->found == 0)
		return (simple_redir_exec(tmp, set_fd, newenv));
	return (2);
}

//in NODE == PIPELINE
// if (!close_file(&set_fd->infile_fd, &set_fd->outfile_fd))
// {
//     close_safe(set_fd, newenv);
//     return (false);
// }
