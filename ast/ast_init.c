/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 20:47:35 by lzannis           #+#    #+#             */
/*   Updated: 2025/10/13 18:02:52 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_create_node_cmd(t_ASTNode *node)
{
	node->argv = NULL;
	node->quotes = NULL;
}

void	init_new_node(t_ASTNode *node, t_Parser *p)
{
	node->r_heredoc = 0;
	node->str = p->current->text;
	node->argv = NULL;
	node->quotes = NULL;
	p->current = p->current->next;
}

void	init_new_node1(t_ASTNode *node)
{
	node->cmd = NULL;
	node->cmd1 = NULL;
	node->left = NULL;
	node->right = NULL;
}
