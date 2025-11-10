/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:40:15 by lzannis           #+#    #+#             */
/*   Updated: 2025/10/16 04:59:18 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	awaiting_children(t_set_fd *set_fd, pid_t *pid)
{
	int	status;
	int	j;

	status = 0;
	j = 0;
	while (j < set_fd->nbcmds)
	{
		if (waitpid(pid[j], &status, 0) < 0)
		{
			perror("waitpid");
			set_fd->last_exit_status = 1;
			return ;
		}
		j++;
	}
	if (WIFEXITED(status))
		set_fd->last_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		set_fd->last_exit_status = 128 + WTERMSIG(status);
	else
		set_fd->last_exit_status = 1;
}

void	fork_fail(t_set_fd *set_fd, char ***newenv)
{
	perror("fork");
	set_fd->last_exit_status = 1;
	free_exec(set_fd, newenv);
	exit(EXIT_FAILURE);
}

bool	is_an_absolut_simple(t_ASTNode *node, t_set_fd *set_fd, char ***newenv)
{
	if (!ft_strchr(node->argv[0], '/'))
		return (false);
	if (access(node->argv[0], F_OK | X_OK) != 0)
	{
		perror("access absolut path");
		return (false);
	}
	execve(node->argv[0], node->argv, *newenv);
	exec_error_handler(set_fd, node->argv[0], newenv);
	free_exec(set_fd, newenv);
	exit(EXIT_FAILURE);
}

void	exec_builtins(t_ASTNode *node, t_set_fd *set_fd, char ***newenv)
{
	if (check_is_a_builtin(&node->argv[0]))
	{
		is_a_builtin(node, newenv, set_fd);
		free_builtins(set_fd, newenv);
		exit(EXIT_SUCCESS);
	}
}

bool	execute_cmd_child_simple(t_ASTNode *node, \
t_set_fd *set_fd, char ***newenv)
{
	if (!piping1_and_piping2(set_fd, newenv))
		return (false);
	setup_signals_fork();
	exec_builtins(node, set_fd, newenv);
	if (!is_an_absolut_simple(node, set_fd, newenv))
	{
		check_path(node, set_fd);
		if (node->cmd1 == NULL)
		{
			set_fd->last_exit_status = 127;
			exec_error_handler(set_fd, node->argv[0], newenv);
		}
		close_all_pipes(set_fd);
		if (!close_file(&set_fd->infile_fd, &set_fd->outfile_fd))
		{
			close_safe(set_fd, newenv);
			return (false);
		}
		execve(node->cmd1, node->argv, *newenv);
		exec_error_handler(set_fd, node->argv[0], newenv);
	}
	return (true);
}
