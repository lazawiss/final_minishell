/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 01:03:35 by imirzaev          #+#    #+#             */
/*   Updated: 2025/10/16 05:12:54 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_ASTNode	*parse_simple_command(t_Parser *p)
{
	t_Token		*tmp;
	t_ASTNode	*cmd;

	cmd = NULL;
	if (match(p, TOKEN_WORD))
	{
		tmp = p->current;
		p->argv_count = 0;
		while (tmp && tmp->type == TOKEN_WORD)
		{
			p->argv_count++;
			tmp = tmp->next;
		}
		cmd = new_node_parser(NODE_COMMAND, p);
		p->val++;
	}
	if (!cmd)
		return (NULL);
	return (cmd);
}

t_ASTNode	*parse_one_redirection(t_Parser *p)
{
	t_ASTNode	*redir;

	redir = NULL;
	if (p->current->type == TOKEN_REDIR_OUT)
		redir = new_node_parser(NODE_REDIR_OUT, p);
	else if (p->current->type == TOKEN_REDIR_OUT_APPEND)
		redir = new_node_parser(NODE_REDIR_OUT_APPEND, p);
	else if (p->current->type == TOKEN_REDIR_IN)
		redir = new_node_parser(NODE_REDIR_IN, p);
	else if (p->current->type == TOKEN_HEREDOC)
		redir = new_node_parser(NODE_HEREDOC, p);
	else if (p->current->type == TOKEN_FD_REDIR)
		redir = new_node_parser(NODE_REDIR_OUT, p);
	else
		return (NULL);
	if (redir)
		p->val++;
	return (redir);
}

t_ASTNode	*parse_redirections(t_Parser *p, t_ASTNode *cmd)
{
	t_ASTNode	*root;
	t_ASTNode	*redir;

	root = cmd;
	while (p->current)
	{
		redir = parse_one_redirection(p);
		if (!redir)
			break ;
		if (!redir)
			return (parser_error(redir, p));
		p->current = p->current->next;
		redir->right = root;
		redir->left = parse_command(p);
		root = redir;
	}
	return (root);
}
