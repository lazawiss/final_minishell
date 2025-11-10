/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 22:10:51 by leazannis         #+#    #+#             */
/*   Updated: 2025/10/16 23:31:50 by imirzaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*append_str(char **buf, const char *s)
{
	char	*tmp;

	if (!s)
		return (*buf);
	if (!*buf)
	{
		*buf = ft_strdup(s);
		if (!*buf)
			return (NULL);
		return (*buf);
	}
	tmp = malloc(ft_strlen(*buf) + ft_strlen(s) + 1);
	if (!tmp)
		return (NULL);
	ft_strcpy(tmp, *buf);
	ft_strcat(tmp, s);
	free(*buf);
	*buf = tmp;
	return (*buf);
}

char	*append_char(char **buf, char c)
{
	char	str[2];

	str[0] = c;
	str[1] = '\0';
	return (append_str(buf, str));
}

void	expand_ast(t_ASTNode *ast, t_set_fd *set_fd, char ***newenv)
{
	t_expand_argv_input	in;

	if (!ast)
		return ;
	if (ast->type == NODE_COMMAND)
	{
		in.argv_ptr = &ast->argv;
		in.parts_ptr = &ast->parts;
		in.quotes_ptr = &ast->quotes;
		in.newenv = newenv;
		in.set_fd = set_fd;
		expand_argv(in);
	}
	if (ast->left)
		expand_ast(ast->left, set_fd, newenv);
	if (ast->right)
		expand_ast(ast->right, set_fd, newenv);
}
