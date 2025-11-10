/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 02:06:10 by lzannis           #+#    #+#             */
/*   Updated: 2025/10/16 05:09:51 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	close_file(int *infile, int *outfile)
{
	if (*infile > 2 && (!close_fd(infile)))
	{
		perror("close infile");
		return (false);
	}
	if (*outfile > 2 && (!close_fd(outfile)))
	{
		perror("close outfile");
		return (false);
	}
	return (true);
}

bool	dup_file_redir_in(t_set_fd *set_fd)
{
	if (dup2(set_fd->infile_fd, STDIN_FILENO) == -1)
	{
		perror("dup2 tmp->infile_fd");
		return (true);
	}
	if (!close_fd(&set_fd->infile_fd))
		return (false);
	return (true);
}

bool	dup_file_redir_out(t_set_fd *set_fd)
{
	if (dup2(set_fd->outfile_fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 exec->outfile_fd");
		return (true);
	}
	if (!close_fd(&set_fd->outfile_fd))
		return (false);
	return (true);
}

bool	dup_file_redir_append(t_set_fd *set_fd)
{
	if (dup2(set_fd->outfile_fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 exec->outfile_fd");
		return (true);
	}
	if (!close_fd(&set_fd->outfile_fd))
	{
		perror(" close exec->outfile_fd");
		return (false);
	}
	return (true);
}
