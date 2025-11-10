/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 00:11:15 by lzannis           #+#    #+#             */
/*   Updated: 2025/10/16 23:47:10 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// ast.c
void	free_partial_argv(char **argv, int count)
{
	while (count >= 0)
	{
		free(argv[count]);
		count--;
	}
}

static void	fill_node_command_entries(t_ASTNode *node, t_Parser *p)
{
	int	i;

	i = 0;
	while (i < p->argv_count && p->current)
	{
		if (p->current->text != NULL)
			node->argv[i] = ft_strdup(p->current->text);
		else
			node->argv[i] = ft_strdup("");
		if (!node->argv[i])
		{
			free_partial_argv(node->argv, i - 1);
			parser_error(node, p);
		}
		node->quotes[i] = p->current->quote;
		node->parts[i] = p->current->parts;
		p->current->parts = NULL;
		p->current = p->current->next;
		i++;
	}
	node->argv[i] = NULL;
}

char	**create_node_command(t_ASTNode *node, t_Parser *p)
{
	init_create_node_cmd(node);
	if (p->argv_count > 0)
	{
		node->argv = malloc(sizeof(char *) * (p->argv_count + 1));
		node->quotes = malloc(sizeof(t_QtType) * p->argv_count);
		node->parts = ft_calloc(p->argv_count, sizeof(t_wordpart *));
		if (!node->argv || !node->quotes || !node->parts)
			parser_error(node, p);
		fill_node_command_entries(node, p);
	}
	else
		init_create_node_cmd(node);
	return (node->argv);
}

char	**create_node_redir(t_ASTNode *redir, t_Parser *p)
{
	p->current = p->current->next;
	redir->argv = malloc(sizeof(char *) * 2);
	if (!redir->argv)
		parser_error(redir, p);
	redir->quotes = malloc(sizeof(t_QtType) * 1);
	if (!redir->quotes)
		parser_error(redir, p);
	redir->parts = ft_calloc(1, sizeof(t_wordpart *));
	if (!redir->parts)
		parser_error(redir, p);
	if (!redir->argv || !redir->quotes)
		parser_error(redir, p);
	redir->argv[0] = ft_strdup(p->current->text);
	if (!redir->argv[0])
		parser_error(redir, p);
	redir->r_heredoc = -1;
	redir->quotes[0] = p->current->quote;
	redir->parts[0] = p->current->parts;
	p->current->parts = NULL;
	redir->argv[1] = NULL;
	return (redir->argv);
}

t_ASTNode	*new_node_parser(t_NodeType type, t_Parser *p)
{
	t_ASTNode	*node;

	node = NULL;
	node = malloc(sizeof(t_ASTNode));
	if (!node)
		return (NULL);
	ft_memset(node, 0, sizeof(t_ASTNode));
	node->val = p->val;
	node->type = type;
	if (node->type == NODE_COMMAND)
	{
		node->argv = create_node_command(node, p);
		if (!node->argv && p->argv_count > 0)
			return (NULL);
		node->str = NULL;
	}
	else if (is_a_redir(node->type))
	{
		node->str = p->current->text;
		node->argv = create_node_redir(node, p);
	}
	else
		init_new_node(node, p);
	init_new_node1(node);
	return (node);
}
