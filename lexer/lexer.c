/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 16:09:37 by imirzaev          #+#    #+#             */
/*   Updated: 2025/10/17 00:15:41 by imirzaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	append_wordpart(t_wordpart **list, const char *text, t_QtType quote)
{
	t_wordpart	*node;
	t_wordpart	*it;

	node = new_wordpart(text, quote);
	if (!node)
		return ;
	if (*list == NULL)
	{
		*list = node;
		return ;
	}
	it = *list;
	while (it->next)
		it = it->next;
	it->next = node;
}

void	free_wordpart_list(t_wordpart *list)
{
	t_wordpart	*next;

	while (list)
	{
		next = list->next;
		if (list->text)
			free(list->text);
		free(list);
		list = next;
	}
}

size_t	calculate_parts_length(t_wordpart *parts)
{
	size_t		total;
	t_wordpart	*it;

	total = 0;
	it = parts;
	while (it)
	{
		if (it->text)
			total += ft_strlen(it->text);
		it = it->next;
	}
	return (total);
}

static char	*handle_word_build_and_validate(const char **p,
		t_Token *cur, t_read *ctx)
{
	char	*merged;

	ft_memset(ctx, 0, sizeof(t_read));
	ctx->p = *p;
	*p = read_word(cur, ctx);
	if (ctx->unclosed)
	{
		if (ctx->out)
			free(ctx->out);
		if (ctx->parts)
			free_wordpart_list(ctx->parts);
		return (NULL);
	}
	merged = join_parts_to_string(ctx->parts);
	if (!merged)
	{
		merged = ft_strdup("");
		if (!merged)
		{
			if (ctx->parts)
				free_wordpart_list(ctx->parts);
			return (NULL);
		}
	}
	return (merged);
}

t_Token	*handle_word(const char **p, t_Token *cur)
{
	t_read	ctx;
	char	*merged;

	merged = handle_word_build_and_validate(p, cur, &ctx);
	if (!merged)
		return (NULL);
	cur->next = new_token(cur, TOKEN_WORD, merged, QUOTE_NONE);
	if (!cur->next)
	{
		free(merged);
		if (ctx.parts)
			free_wordpart_list(ctx.parts);
		return (NULL);
	}
	cur->next->parts = ctx.parts;
	return (cur->next);
}
