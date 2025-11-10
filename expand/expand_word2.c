/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imirzaev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 23:28:49 by imirzaev          #+#    #+#             */
/*   Updated: 2025/10/16 23:29:15 by imirzaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_env_variable(t_expand_ctx *ctx)
{
	char	*val;

	ctx->start = ctx->i;
	while (ctx->word[ctx->i] && (ft_isalnum((unsigned char)ctx->word[ctx->i])
			|| ctx->word[ctx->i] == '_'))
		ctx->i++;
	ctx->tmp = ft_substr(ctx->word, ctx->start, ctx->i - ctx->start);
	val = get_env_value(ctx->env, ctx->tmp);
	free(ctx->tmp);
	if (val)
		append_str(&ctx->buf, val);
}

void	expand_dollar_case(t_expand_ctx *ctx, t_set_fd *set_fd)
{
	if (ctx->word[ctx->i] == '?')
	{
		ctx->tmp = ft_itoa(set_fd->last_exit_status);
		append_str(&ctx->buf, ctx->tmp);
		free(ctx->tmp);
		ctx->i++;
	}
	else if (ctx->word[ctx->i] == '$')
	{
		append_str(&ctx->buf, "$$");
		ctx->i++;
	}
	else if (ft_isalpha((unsigned char)ctx->word[ctx->i])
		|| ctx->word[ctx->i] == '_')
		expand_env_variable(ctx);
	else
		append_char(&ctx->buf, '$');
}
