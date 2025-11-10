/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imirzaev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 00:20:42 by imirzaev          #+#    #+#             */
/*   Updated: 2025/10/17 00:22:21 by imirzaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*prepare_segment_after_quote(t_read *ctx)
{
	char	*segment;

	if (!ctx->out)
		segment = ft_strdup("");
	else
		segment = ft_strdup(ctx->out);
	if (!segment)
	{
		if (ctx->out)
		{
			free(ctx->out);
			ctx->out = NULL;
		}
		return (NULL);
	}
	if (ctx->out)
	{
		free(ctx->out);
		ctx->out = NULL;
	}
	return (segment);
}

char	*consume_quoted_segment_core(t_Token *token, t_read *ctx, t_QtType *qt)
{
	char	*segment;

	if (*ctx->p == '\'')
		*qt = QUOTE_SINGLE;
	else
		*qt = QUOTE_DOUBLE;
	ctx->p = read_quoted(token, ctx, *ctx->p);
	if (ctx->unclosed)
		return ((char *)ctx->p);
	segment = prepare_segment_after_quote(ctx);
	return (segment);
}
