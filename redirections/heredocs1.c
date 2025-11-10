/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 18:57:41 by lzannis           #+#    #+#             */
/*   Updated: 2025/10/16 05:12:21 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	dup_heredoc(t_ASTNode *node, int *pfd, t_set_fd *set_fd)
{
	if (!close_fd(&pfd[1]))
	{
		perror("close_fd[1] HEREDOC");
		return (false);
	}
	if (set_fd->is_heredoc == true || g_sig == 130)
	{
		if (!close_fd(&pfd[0]))
		{
			perror("close_fd[0] HEREDOC");
			return (false);
		}
		return (true);
	}
	node->r_heredoc = dup(pfd[0]);
	if (!close_fd(&pfd[0]))
	{
		perror("close_fd[0] HEREDOC");
		return (false);
	}
	if (node->r_heredoc == -1 && errno != EBADF)
		return (perror("dup HEREDOC"), false);
	return (true);
}
