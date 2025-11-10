/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 04:42:23 by lzannis           #+#    #+#             */
/*   Updated: 2025/10/17 00:28:38 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	search_heredocs(t_ASTNode *tmp, t_set_fd *set_fd)
{
	if (tmp->type == NODE_HEREDOC || tmp->type == NODE_REDIR_IN)
	{
		set_fd->is_heredoc = true;
		return ;
	}
	if (tmp->left)
		search_heredocs(tmp->left, set_fd);
	if (tmp->right)
		search_heredocs(tmp->right, set_fd);
}

bool	open_heredocs(t_ASTNode *tmp, t_set_fd *set_fd)
{
	set_fd->is_heredoc = false;
	if (tmp->left)
		search_heredocs(tmp->left, set_fd);
	if (g_sig != 130)
		g_sig = 2;
	install_heredoc_signals();
	if (!heredoc_to_stdin(tmp, tmp->argv[0], set_fd))
		return (false);
	setup_signals();
	return (true);
}

void	search_builtin(t_ASTNode *tmp, t_set_fd *set_fd)
{
	if (tmp->type == NODE_COMMAND)
	{
		if (check_is_a_builtin(&tmp->argv[0]))
			set_fd->is_builtin = true;
		set_fd->found++;
	}
	if (tmp->type == NODE_PIPELINE)
		set_fd->nbpipes++;
	if (tmp->type == NODE_HEREDOC)
	{
		if (!open_heredocs(tmp, set_fd))
			return ;
	}
	if (tmp->left)
		search_builtin(tmp->left, set_fd);
	if (tmp->right)
		search_builtin(tmp->right, set_fd);
}

bool	check_redir(t_ASTNode *tmp, t_set_fd *set_fd)
{
	if (is_a_redir(tmp->type))
	{
		if (!check_file(tmp, set_fd))
			return (false);
	}
	if (tmp->left)
	{
		if (!check_redir(tmp->left, set_fd))
			return (false);
	}
	if (tmp->right)
	{
		if (!check_redir(tmp->right, set_fd))
			return (false);
	}
	return (true);
}

void	execute_simple_builtin(t_ASTNode *tmp, t_set_fd *set_fd, char ***newenv)
{
	if (!check_redir(tmp, set_fd))
		return ;
	if (!piping1_and_piping2(set_fd, newenv))
		return ;
	tmp = search_cmds(tmp);
	is_a_builtin(tmp, newenv, set_fd);
}
