/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 04:19:31 by lzannis           #+#    #+#             */
/*   Updated: 2025/10/16 17:06:22 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	close_exec_simple(t_set_fd *set_fd, char ***newenv)
{
	if (set_fd->left_pid)
		awaiting_children_single(set_fd, set_fd->left_pid);
	g_sig = 0;
	if (!close_fd(&set_fd->new_stdin))
		return (false);
	if (!close_fd(&set_fd->new_stdout))
		return (false);
	if (!close_file(&set_fd->infile_fd, &set_fd->outfile_fd))
	{
		close_safe(set_fd, newenv);
		return (false);
	}
	return (true);
}

void	awaiting_children_single(t_set_fd *set_fd, pid_t pid)
{
	int	status;

	status = 0;
	if (waitpid(pid, &status, 0) < 0)
	{
		perror("waitpid");
		set_fd->last_exit_status = 1;
		return ;
	}
	if (WIFEXITED(status))
		set_fd->last_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		set_fd->last_exit_status = 128 + WTERMSIG(status);
	else
		set_fd->last_exit_status = 1;
}

bool	exec_node_command_single(t_ASTNode *tmp, t_set_fd *set_fd, \
char ***newenv)
{
	g_sig = 1;
	set_fd->left_pid = fork();
	if (set_fd->left_pid < 0)
		fork_fail(set_fd, newenv);
	else if (set_fd->left_pid == 0)
	{
		if (!execute_cmd_child_simple(tmp, set_fd, newenv))
			return (false);
	}
	return (true);
}

// <infile | >outfile <infile cat <<EOF | cat | cat
bool	exec_single(t_ASTNode *tmp, t_set_fd *set_fd, char ***newenv)
{
	if (is_a_redir(tmp->type))
	{
		if (!check_file(tmp, set_fd))
			return (false);
		if (tmp->left)
			exec_single(tmp->left, set_fd, newenv);
		if (tmp->right)
			exec_single(tmp->right, set_fd, newenv);
	}
	if (tmp->type == NODE_COMMAND)
	{
		if (!exec_node_command_single(tmp, set_fd, newenv))
			return (false);
	}
	return (true);
}
