/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 19:22:03 by lzannis           #+#    #+#             */
/*   Updated: 2025/10/16 19:33:05 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// open pipe 
void	set_pipe(t_set_fd *set_fd, char ***newenv)
{
	if (set_fd->i < set_fd->nbcmds - 1)
	{
		if (pipe(set_fd->next_pipe) == -1)
		{
			perror("pipe");
			close_safe(set_fd, newenv);
		}
	}
}

// stock sdtin and stdout cause dup2 write over it
bool	dup_stds(int *new_stdin, int *new_stdout, int oldstdin, int oldstdout)
{
	*new_stdin = dup(oldstdin);
	if (*new_stdin == -1 && errno != EBADF)
	{
		perror("dup new_stdin");
		return (false);
	}
	*new_stdout = dup(oldstdout);
	if (*new_stdout == -1 && errno != EBADF)
	{
		perror("dup new_stdout");
		return (false);
	}
	return (true);
}

// reset stdin/stdout 
bool	reset_stds(int new_stdin, int new_stdout)
{
	if (dup2(new_stdin, STDIN_FILENO) == -1)
	{
		perror("dup2 reset new_stdin");
		return (false);
	}
	if (!close_fd(&new_stdin))
	{
		perror("close reset new_stdin");
		return (false);
	}
	if (dup2(new_stdout, STDOUT_FILENO) == -1)
	{
		perror("dup2 reset new_stdout");
		return (false);
	}
	if (!close_fd(&new_stdout))
	{
		perror("close reset new_stdout");
		return (false);
	}
	return (true);
}

// bool	dup_prev_pipe(int *pfd)
bool	dup_prev_pipe(t_set_fd *set_fd)
{
	if (dup2(set_fd->prev_pipe[READ_END], STDIN_FILENO) == -1)
	{
		perror("dup2 prev read");
		return (false);
	}
	if (!close_fd(&set_fd->prev_pipe[READ_END]))
		return (false);
	return (true);
}

// bool	dup_next_pipe(int *pfd)
bool	dup_next_pipe(t_set_fd *set_fd)
{
	if (dup2(set_fd->next_pipe[WRITE_END], STDOUT_FILENO) == -1)
	{
		perror("dup2 next write");
		return (false);
	}
	if (!close_pipe(set_fd->next_pipe))
		return (false);
	return (true);
}
