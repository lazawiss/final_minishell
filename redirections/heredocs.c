/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 01:58:08 by lzannis           #+#    #+#             */
/*   Updated: 2025/10/13 21:35:46 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	set_pipe_heredoc(int pfd[2])
{
	if (pipe(pfd) < 0)
	{
		perror("pipe");
		if (!close_pipe(pfd))
			return (false);
		return (false);
	}
	return (true);
}

bool	write_error(t_heredoc *heredoc)
{
	if (write(heredoc->pfd[1], heredoc->buf, (heredoc->len + 1)) < 0)
	{
		perror("write");
		if (!close_pipe(heredoc->pfd))
			return (false);
		return (false);
	}
	return (true);
}

void	error_msg_heredoc(const char *delim)
{
	ft_putstr_fd("minish-elles: warning: \
	here-document delimited by end-of-file", 2);
	ft_putstr_fd("(wanted `", 2);
	ft_putstr_fd((char *)delim, 2);
	ft_putendl_fd("')", 2);
}

size_t	read_heredoc(t_heredoc *heredoc)
{
		heredoc->r = read(STDIN_FILENO, &heredoc->buf[heredoc->len], 1);
	while (heredoc->r > 0)
	{
		if (heredoc->r == -1 && errno == EINTR)
			return (-1);
		if (heredoc->buf[heredoc->len] == '\n')
			break ;
		if (heredoc->len >= sizeof(heredoc->buf) - 1)
			break ;
		heredoc->len++;
		heredoc->r = read(STDIN_FILENO, &heredoc->buf[heredoc->len], 1);
	}
	return (heredoc->len);
}

bool	heredoc_to_stdin(t_ASTNode *node, const char *delim, t_set_fd *set_fd)
{
	t_heredoc	heredoc;

	if (!set_pipe_heredoc(heredoc.pfd))
		return (false);
	heredoc.r = 0;
	while (g_sig != 130)
	{
		heredoc.len = 0;
		write(1, "> ", 2);
		heredoc.len = read_heredoc(&heredoc);
		if (g_sig == 2 && heredoc.r <= 0)
		{
			error_msg_heredoc(delim);
			break ;
		}
		heredoc.buf[heredoc.len] = '\0';
		if (ft_strcmp(heredoc.buf, delim) == 0)
			break ;
		heredoc.buf[heredoc.len] = '\n';
		if (!write_error(&heredoc))
			return (false);
	}	
	if (!dup_heredoc(node, heredoc.pfd, set_fd))
		return (false);
	return (true);
}
