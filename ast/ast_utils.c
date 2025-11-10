/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 20:57:05 by lzannis           #+#    #+#             */
/*   Updated: 2025/10/16 23:36:11 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	print_depth_first_search_recursiv(t_ASTNode *node, int depth)
// {
// 	int	i;

// 	if (!node)
// 		return ;
// 	for (int d = 0; d < depth; d++)
// 		printf("  ");
// 	if (!node->argv)
// 	{
// 		printf("no astargv ");
// 		printf("aststr = %s ", node->str);
// 		printf(" no r_heredoc ");
// 	}
// 	else
// 	{
// 		i = 0;
// 		while (node->argv[i])
// 		{
// 			printf("astargv[%d] = %s ", i, node->argv[i]);
// 			i++;
// 		}
// 		if (node->str)
// 			printf("aststr = %s ", node->str);
// 		else
// 			printf("aststr = NULL ");
// 		if (node->type != NODE_COMMAND && node->r_heredoc)
// 			printf("r_heredoc = %d\n", node->r_heredoc);
// 	}
// 	printf("val = %d asttype = %d \n", node->val, node->type);
// 	if (node->left)
// 	{
// 		fprintf(stderr, "left val = %d\n", node->val);
// 		print_depth_first_search_recursiv(node->left, depth + 1);
// 	}
// 	if (node->right)
// 	{
// 		fprintf(stderr, "right val = %d\n", node->val);
// 		print_depth_first_search_recursiv(node->right, depth + 1);
// 	}
// }

static int	count_argv(char **argv)
{
	int	n;

	n = 0;
	if (!argv)
		return (0);
	while (argv[n])
		n++;
	return (n);
}

bool	is_a_redir(t_NodeType type)
{
	return (type == NODE_REDIR_IN \
		|| type == NODE_REDIR_OUT \
		||type == NODE_HEREDOC \
		||type == NODE_REDIR_OUT_APPEND);
}

static void	free_parts_array(t_ASTNode *node)
{
	int			argc;
	t_wordpart	**pp;

	if (!node || !node->parts)
		return ;
	argc = count_argv(node->argv);
	pp = node->parts;
	while (argc-- > 0 && pp)
	{
		if (*pp)
			free_wordpart_list(*pp);
		pp++;
	}
	free(node->parts);
	node->parts = NULL;
}

static void	free_node_fields(t_ASTNode *node)
{
	if (!node)
		return ;
	if (node->argv)
		ft_free(node->argv);
	if (node->quotes)
		free(node->quotes);
	if (node->cmd1)
		free(node->cmd1);
	node->argv = NULL;
	node->quotes = NULL;
	node->cmd = NULL;
	node->cmd1 = NULL;
}

void	free_ast(t_ASTNode *node)
{
	if (!node)
		return ;
	if (node->left)
		free_ast(node->left);
	if (node->right)
		free_ast(node->right);
	free_parts_array(node);
	free_node_fields(node);
	free(node);
}

// void	free_ast_iterative(ASTNode *root)
// {
// 	ASTNode	*stack[256];
// 	ASTNode	*node;
// 	int		top;
// 	int		i;	
// 	top = 0;
// 	i = 0;
// 	if (!root)
// 		return ;
// 	stack[top++] = root;
// 	while (top > 0)
// 	{
// 		node = stack[--top];
// 		i = 0;
// 		if (node->argv)
// 		{
// 			while (node->argv[i])
// 			{
// 				free(node->argv[i]);
// 				i++;
// 			}
// 			free(node->argv);
// 		}
// 		if (node->quotes)
// 			free(node->quotes);
// 		if (node->left)
// 			stack[top++] = node->left;
// 		if (node->right)
// 			stack[top++] = node->right;
// 		free(node);
// 	}
// }
