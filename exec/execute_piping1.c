/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_piping1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 00:10:24 by lzannis           #+#    #+#             */
/*   Updated: 2025/10/11 02:52:43 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// dup fd for the pipes
bool	piping1(t_set_fd *set_fd)
{
	if (set_fd->infile_fd > 0)
	{
		if (!dup_file_redir_in(set_fd))
			return (false);
	}
	else
	{
		if (set_fd->i > 0)
		{
			if (!dup_prev_pipe(set_fd))
				return (false);
		}
	}
	return (true);
}

bool	piping2(t_set_fd *set_fd)
{
	if (set_fd->outfile_fd > 0)
	{
		if (!dup_file_redir_out(set_fd))
			return (false);
	}
	else
	{
		if (set_fd->i < set_fd->nbcmds - 1)
		{
			if (!dup_next_pipe(set_fd))
				return (false);
		}
	}
	return (true);
}

bool	piping1_and_piping2(t_set_fd *set_fd, char ***newenv)
{
	if (!piping1(set_fd))
	{
		close_safe(set_fd, newenv);
		return (false);
	}
	if (!piping2(set_fd))
	{
		close_safe(set_fd, newenv);
		return (false);
	}
	return (true);
}
