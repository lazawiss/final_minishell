/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 16:52:31 by imirzaev          #+#    #+#             */
/*   Updated: 2025/10/16 23:28:22 by imirzaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_variable_expansion(t_expand_ctx *ctx, t_set_fd *set_fd)
{
	ctx->start_i = ctx->i++;
	if (ctx->word[ctx->i] == '\0')
	{
		append_char(&ctx->buf, '$');
		return ;
	}
	expand_dollar_case(ctx, set_fd);
}

void	process_word_loop(t_expand_ctx *ctx, t_set_fd *set_fd)
{
	while (ctx->word[ctx->i])
	{
		if (ctx->qtype == QUOTE_DOUBLE && ctx->word[ctx->i] == '\\')
		{
			ctx->i++;
			if (ctx->word[ctx->i])
				append_char(&ctx->buf, ctx->word[ctx->i++]);
		}
		else if (ctx->word[ctx->i] == '$')
			handle_variable_expansion(ctx, set_fd);
		else
			append_char(&ctx->buf, ctx->word[ctx->i++]);
	}
}

char	*expand_word(const char *w, t_QtType qtype,
		t_set_fd *set_fd, char **nwnv)
{
	t_expand_ctx	ctx;
	char			*dup;
	char			*empty;

	ctx.word = w;
	ctx.qtype = qtype;
	ctx.env = nwnv;
	ctx.buf = NULL;
	ctx.i = 0;
	if (ctx.qtype == QUOTE_SINGLE)
	{
		dup = ft_strdup(ctx.word);
		if (!dup)
			return (NULL);
		return (dup);
	}
	process_word_loop(&ctx, set_fd);
	if (!ctx.buf)
	{
		empty = ft_strdup("");
		if (!empty)
			return (NULL);
		return (empty);
	}
	return (ctx.buf);
}

static int	expand_from_parts_loop(t_wordpart *cur, t_set_fd *set_fd,
		char **newenv, char **out)
{
	const char	*src;
	char		*piece;

	while (cur)
	{
		if (cur->text)
			src = cur->text;
		else
			src = "";
		piece = expand_word(src, cur->quote, set_fd, newenv);
		if (!piece)
		{
			piece = ft_strdup("");
			if (!piece)
				return (0);
		}
		if (!append_str(out, piece))
		{
			free(piece);
			return (0);
		}
		free(piece);
		cur = cur->next;
	}
	return (1);
}

char	*expand_from_parts(t_wordpart *parts, t_set_fd *set_fd, char **newenv)
{
	char		*out;

	out = NULL;
	if (!expand_from_parts_loop(parts, set_fd, newenv, &out))
		return (NULL);
	if (!out)
	{
		out = ft_strdup("");
		if (!out)
			return (NULL);
	}
	return (out);
}
