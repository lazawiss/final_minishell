/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 00:24:23 by imirzaev          #+#    #+#             */
/*   Updated: 2025/10/16 23:27:04 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_tokens(t_Token *tok)
{
	t_Token	*next;

	next = tok;
	while (next)
	{
		next = tok->next;
		if (tok->text)
			free(tok->text);
		if (tok->parts)
			free_wordpart_list(tok->parts);
		free(tok);
		tok = next;
	}
}

int	is_operator_char(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

t_Token	*new_token(t_Token *token, t_TknType type, char *text, t_QtType quote)
{
	t_Token	*tok;
	char	*orig;

	orig = text;
	tok = safe_malloc(token, sizeof(t_Token));
	if (!tok)
		return (NULL);
	tok->type = type;
	tok->quote = quote;
	tok->next = NULL;
	tok->parts = NULL;
	if (text)
		tok->text = ft_strdup(text);
	else
		tok->text = ft_strdup("");
	if (!tok->text)
	{
		free(orig);
		free(tok);
		return (NULL);
	}
	if (orig)
		free(orig);
	return (tok);
}

t_Token	*lexer_process_chunk(const char **p, t_Token *cur)
{
	if (is_operator_char(**p))
		return (handle_operator(p, cur));
	return (handle_word(p, cur));
}

t_Token	*lexer_process_line(const char *line)
{
	t_Token		head;
	t_Token		*cur;
	const char	*p;

	ft_memset(&head, 0, sizeof(t_Token));
	head.next = NULL;
	cur = &head;
	p = line;
	cur = process_lexer_chunks(&p, cur, &head);
	if (!cur)
		return (NULL);
	cur->next = new_token(cur, TOKEN_EOF, ft_strdup(""), QUOTE_NONE);
	if (cur->next)
		cur->next->parts = NULL;
	return (head.next);
}
