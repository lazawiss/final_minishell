/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imirzaev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 00:16:02 by imirzaev          #+#    #+#             */
/*   Updated: 2025/10/17 00:16:04 by imirzaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	copy_parts_into_buffer(t_wordpart *parts, char *s)
{
	size_t		i;
	size_t		j;
	t_wordpart	*it;

	i = 0;
	it = parts;
	while (it)
	{
		j = 0;
		if (it->text)
		{
			while (it->text[j])
			{
				s[i] = it->text[j];
				i = i + 1;
				j = j + 1;
			}
		}
		it = it->next;
	}
	s[i] = '\0';
}

char	*join_parts_to_string(t_wordpart *parts)
{
	size_t	total;
	char	*s;

	total = calculate_parts_length(parts);
	s = (char *)malloc(total + 1);
	if (!s)
		return (NULL);
	copy_parts_into_buffer(parts, s);
	return (s);
}

void	finalize_unquoted_segment(t_Token *token, t_read *ctx)
{
	(void)token;
	if (ctx->out)
	{
		append_wordpart(&ctx->parts, ctx->out, QUOTE_NONE);
		free(ctx->out);
		ctx->out = NULL;
	}
}

const char	*consume_quoted_segment(t_Token *token, t_read *ctx)
{
	char		*segment;
	t_QtType	qt;

	segment = consume_quoted_segment_core(token, ctx, &qt);
	if (!segment)
		return (NULL);
	if (ctx->unclosed)
		return (ctx->p);
	append_wordpart(&ctx->parts, segment, qt);
	free(segment);
	return (ctx->p);
}

const char	*read_word(t_Token *token, t_read *ctx)
{
	ctx->out = NULL;
	ctx->parts = NULL;
	ctx->qtype = QUOTE_NONE;
	while (*(ctx->p) && !ft_is_space_char((unsigned char)*(ctx->p))
		&& !is_operator_char(*(ctx->p)))
	{
		if (*(ctx->p) == '\'' || *(ctx->p) == '"')
		{
			finalize_unquoted_segment(token, ctx);
			ctx->p = consume_quoted_segment(token, ctx);
			if (ctx->unclosed)
				return (ctx->p);
		}
		else
			append_char_lexer(token, &ctx->out, *(ctx->p)++);
	}
	finalize_unquoted_segment(token, ctx);
	return (ctx->p);
}
