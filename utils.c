/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 20:30:39 by lzannis           #+#    #+#             */
/*   Updated: 2025/10/13 21:39:55 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(t_ASTNode *ast, t_set_fd *set_fd, char ***newenv)
{
	rl_clear_history();
	if (ast)
		free_ast(ast);
	if (*newenv)
		ft_free(*newenv);
	if (set_fd)
		free_set_fd(set_fd);
	if (set_fd->new_stdin)
		close_fd(&set_fd->new_stdin);
	if (set_fd->new_stdout)
		close_fd(&set_fd->new_stdout);
	return ;
}

int	match(t_Parser *p, t_TknType type)
{
	if (p->current == NULL)
	{
		return (0);
	}
	if (p->current->type == type)
		return (1);
	return (0);
}

char	*ft_strncpy(char *dest, const char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

void	print_node(t_Token *pargs)
{
	t_Token	*tmp;

	tmp = pargs;
	while (tmp)
	{
		fprintf(stderr, "token = %d\n", tmp->type);
		fprintf(stderr, "text = %s\n", tmp->text);
		fprintf(stderr, "quote = %d\n", tmp->quote);
		tmp = tmp->next;
	}
}

// void	print_node_parser(Parser *pargs)
// {
// 	Parser	*tmp;

// 	tmp = pargs;
// 	while (tmp && tmp->current->next)
// 	{
// 		fprintf(stderr, "token = %d\n", tmp->current->type);
// 		fprintf(stderr, "text = %s\n", tmp->current->text);
// 		fprintf(stderr, "quote = %d\n", tmp->current->quote);
// 		tmp->current = tmp->current->next;
// 		fprintf(stderr, "val = %d\n", tmp->val);
// 		fprintf(stderr, "argv-count = %d\n", tmp->argv_count);
// 	}
// }
