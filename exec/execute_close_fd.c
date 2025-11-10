/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_close_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 03:14:23 by lzannis           #+#    #+#             */
/*   Updated: 2025/10/16 05:03:10 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
//ls | cat -e | cat -e | cat -e | cat -e
// ls -l | grep ^- | cat | wc -l

void	close_safe(t_set_fd *set_fd, char ***newenv)
{
	close_pipe(set_fd->prev_pipe);
	close_pipe(set_fd->next_pipe);
	free_set_fd(set_fd);
	ft_free(*newenv);
	exit(EXIT_FAILURE);
}

// close the reading end of prev_pipe if it's not the 1rst cmd
// close the writing end of current pipe
// switch info from current pipe to next pipe 
bool	close_and_switch_pipe(t_set_fd *set_fd)
{
	if (!close_fd(&set_fd->prev_pipe[READ_END]))
		return (false);
	if (!close_fd(&set_fd->next_pipe[WRITE_END]))
		return (false);
	if (set_fd->next_pipe[WRITE_END] != -1)
		set_fd->prev_pipe[WRITE_END] = set_fd->next_pipe[WRITE_END];
	if (set_fd->next_pipe[READ_END] != -1)
		set_fd->prev_pipe[READ_END] = set_fd->next_pipe[READ_END];
	return (true);
}

// close fd safely and set to -1
bool	close_fd(int *fd)
{
	if (*fd != -1)
	{
		if (close(*fd) == -1)
			return (false);
		*fd = -1;
	}
	return (true);
}

bool	close_pipe(int fd[2])
{
	if (! *fd)
		return (false);
	if (!close_fd(&fd[READ_END]))
		return (false);
	if (!close_fd(&fd[WRITE_END]))
		return (false);
	return (true);
}

//close the last 2 pipes that stays open otherwise
void	close_all_pipes(t_set_fd *set_fd)
{
	if (set_fd->prev_pipe[WRITE_END] > 2)
	{
		if (!close_fd(&set_fd->prev_pipe[WRITE_END]))
			perror("close all_pipes prev_pipe w");
	}
	if (set_fd->next_pipe[WRITE_END] > 2)
	{
		if (!close_fd(&set_fd->next_pipe[WRITE_END]))
			perror("close all_pipes next_pipe w");
	}
}
