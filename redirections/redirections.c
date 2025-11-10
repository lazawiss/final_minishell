/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 20:33:55 by lzannis           #+#    #+#             */
/*   Updated: 2025/10/16 17:22:22 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	open_file_redir_in(t_ASTNode *tmp, t_set_fd *set_fd)
{
	if (set_fd->infile_fd > 2)
	{
		if (!close_fd(&set_fd->infile_fd))
		{
			perror("close_fd infile");
			return (false);
		}
	}
	set_fd->infile_fd = open(tmp->argv[0], O_RDONLY, 0644);
	if (set_fd->infile_fd == -1)
	{
		msg_error_open_file(set_fd, tmp->argv[0]);
		return (false);
	}
	return (true);
}

bool	open_file_redir_out(t_ASTNode *tmp, t_set_fd *set_fd)
{
	if (set_fd->outfile_fd > 2)
	{
		if (!close_fd(&set_fd->outfile_fd))
		{
			perror("close_fd outfile");
			return (false);
		}
	}
	set_fd->outfile_fd = open(tmp->argv[0], O_RDONLY | O_WRONLY | O_CREAT \
	| O_TRUNC, 0644);
	if (set_fd->outfile_fd == -1)
	{
		perror("open outfile");
		return (false);
	}
	return (true);
}

bool	open_file_redir_append(t_ASTNode *tmp, t_set_fd *set_fd)
{
	if (set_fd->outfile_fd > 2)
	{
		if (!close_fd(&set_fd->outfile_fd))
		{
			perror("close_fd outfile");
			return (false);
		}
	}
	set_fd->outfile_fd = open(tmp->argv[0], O_APPEND | O_RDONLY | O_WRONLY \
	| O_CREAT, 0644);
	if (set_fd->outfile_fd == -1)
	{
		perror("open append");
		return (false);
	}
	return (true);
}

bool	open_file_redir_heredoc(t_ASTNode *tmp, t_set_fd *set_fd)
{
	if (tmp->r_heredoc > 0)
	{
		if (set_fd->infile_fd > 2 && !close_fd(&set_fd->infile_fd))
		{
			perror("close_fd infile");
			return (false);
		}
		set_fd->infile_fd = dup(tmp->r_heredoc);
		if (!close_fd(&tmp->r_heredoc))
		{
			perror("tmp->r_heredoc");
			return (false);
		}
	}
	return (true);
}

bool	check_file(t_ASTNode *tmp, t_set_fd *set_fd)
{
	if (tmp->type == NODE_REDIR_IN)
	{
		if (!open_file_redir_in(tmp, set_fd))
			return (false);
	}
	else if (tmp->type == NODE_REDIR_OUT)
	{
		if (!open_file_redir_out(tmp, set_fd))
			return (false);
	}
	else if (tmp->type == NODE_REDIR_OUT_APPEND)
	{
		if (!open_file_redir_append(tmp, set_fd))
			return (false);
	}
	else if (tmp->type == NODE_HEREDOC)
	{
		if (!open_file_redir_heredoc(tmp, set_fd))
			return (false);
	}
	return (true);
}
