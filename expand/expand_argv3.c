/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_argv3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imirzaev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 23:04:32 by imirzaev          #+#    #+#             */
/*   Updated: 2025/10/16 23:09:50 by imirzaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_unquoted_split_ctx(t_expand_argv_ctx *ctx)
{
	ctx->j = 0;
	while (ctx->split[ctx->j])
	{
		if (!ensure_cap(&ctx->new_argv, &ctx->cap, ctx->idx + 1))
			return (0);
		ctx->new_argv[ctx->idx] = ft_strdup(ctx->split[ctx->j]);
		if (!ctx->new_argv[ctx->idx])
			return (0);
		ctx->idx = ctx->idx + 1;
		ctx->j = ctx->j + 1;
	}
	return (1);
}

int	process_unquoted_word_ctx(t_expand_argv_ctx *ctx)
{
	ctx->split = split_unquoted(ctx->expanded);
	if (ctx->split)
	{
		if (!handle_unquoted_split_ctx(ctx))
		{
			free(ctx->split);
			free(ctx->expanded);
			return (0);
		}
		free(ctx->split);
	}
	free(ctx->expanded);
	return (1);
}

int	handle_quoted_word_ctx(t_expand_argv_ctx *ctx)
{
	if (!ensure_cap(&ctx->new_argv, &ctx->cap, ctx->idx + 1))
	{
		free(ctx->expanded);
		return (0);
	}
	ctx->new_argv[ctx->idx] = ctx->expanded;
	ctx->idx = ctx->idx + 1;
	return (1);
}

int	process_regular_word_ctx(t_expand_argv_ctx *ctx, t_set_fd *set_fd)
{
	t_QtType	q;

	q = QUOTE_NONE;
	if (ctx->quotes)
		q = ctx->quotes[ctx->i];
	ctx->expanded = expand_word(ctx->argv[ctx->i], q, set_fd, ctx->env);
	if (!ctx->expanded)
	{
		ctx->expanded = ft_strdup("");
		if (!ctx->expanded)
			return (0);
	}
	if (q == QUOTE_NONE)
	{
		if (!process_unquoted_word_ctx(ctx))
			return (0);
	}
	else
	{
		if (!handle_quoted_word_ctx(ctx))
			return (0);
	}
	return (1);
}
