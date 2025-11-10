/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 01:12:29 by imirzaev          #+#    #+#             */
/*   Updated: 2025/10/13 18:17:37 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_ASTNode	*parser_error(t_ASTNode *node, t_Parser *p)
{
	if (node)
		free_ast(node);
	if (p->current->text)
		free(p->current->text);
	exit(EXIT_FAILURE);
}

t_ASTNode	*parse_primary(t_Parser *p)
{
	return (parse_command(p));
}

t_ASTNode	*parse_sequence(t_Parser *p)
{
	return (parse_and_or(p));
}

t_ASTNode	*parse_command(t_Parser *p)
{
	t_ASTNode	*cmd;

	cmd = NULL;
	if (match(p, TOKEN_WORD))
	{
		cmd = parse_simple_command(p);
		if (!cmd)
			return (NULL);
	}
	return (parse_redirections(p, cmd));
}

t_ASTNode	*parse_pipeline(t_Parser *p)
{
	t_ASTNode	*left;
	t_ASTNode	*pipe_node;

	left = parse_primary(p);
	if (!left)
		return (NULL);
	while (match(p, TOKEN_PIPE))
	{
		pipe_node = new_node_parser(NODE_PIPELINE, p);
		p->val++;
		if (!pipe_node)
			return (parser_error(left, p));
		pipe_node->left = left;
		pipe_node->right = parse_primary(p);
		if (!pipe_node->right)
			return (parser_error(pipe_node, p));
		left = pipe_node;
	}
	return (left);
}
