/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 22:06:22 by imirzaev          #+#    #+#             */
/*   Updated: 2025/10/16 23:23:45 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*safe_malloc(t_Token *token, size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		perror("malloc failed");
		free_tokens(token);
		exit(1);
	}
	return (ptr);
}

void	append_char_lexer(t_Token *token, char **buf, char c)
{
	size_t	len;
	char	*tmp;

	if (*buf)
		len = ft_strlen(*buf);
	else
		len = 0;
	tmp = safe_malloc(token, len + 2);
	if (*buf)
	{
		ft_strcpy(tmp, *buf);
		free(*buf);
	}
	tmp[len] = c;
	tmp[len + 1] = '\0';
	*buf = tmp;
}

void	append_str_lexer(t_Token *token, char **buf, const char *s)
{
	size_t	len;
	char	*tmp;

	if (!s)
		return ;
	if (*buf)
		len = ft_strlen(*buf);
	else
		len = 0;
	tmp = safe_malloc(token, len + ft_strlen(s) + 1);
	if (*buf)
	{
		ft_strcpy(tmp, *buf);
		free(*buf);
	}
	ft_strcpy(tmp + len, s);
	*buf = tmp;
}

const char	*read_quoted(t_Token *token, t_read *read, char quote)
{
	if (quote == '\'')
		read->qtype = QUOTE_SINGLE;
	else if (quote == '"')
		read->qtype = QUOTE_DOUBLE;
	read->p++;
	while (*(read->p) && *(read->p) != quote)
		append_char_lexer(token, &read->out, *(read->p)++);
	if (*(read->p) == quote && read->out == NULL)
	{
		read->out = ft_strdup("");
		if (!read->out)
			return (NULL);
	}
	if (!*(read->p))
	{
		read->unclosed = 1;
		return (read->p);
	}
	return (++(read->p));
}

t_wordpart	*new_wordpart(const char *text, t_QtType quote)
{
	t_wordpart	*node;

	node = (t_wordpart *)malloc(sizeof(t_wordpart));
	if (!node)
		return (NULL);
	if (text)
		node->text = ft_strdup(text);
	else
		node->text = ft_strdup("");
	if (!node->text)
	{
		free(node);
		return (NULL);
	}
	node->quote = quote;
	node->next = NULL;
	return (node);
}
