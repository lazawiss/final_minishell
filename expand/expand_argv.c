/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 16:21:47 by imirzaev          #+#    #+#             */
/*   Updated: 2025/10/16 22:54:13 by imirzaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_str_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	count_argv(char **v)
{
	int	n;

	n = 0;
	if (!v)
		return (0);
	while (v[n])
		n++;
	return (n);
}

void	process_each_arg_ctx(t_expand_argv_ctx *ctx, t_set_fd *set_fd)
{
	ctx->total = count_argv(ctx->argv);
	ctx->i = 0;
	while (ctx->i < ctx->total)
	{
		if (ctx->parts && ctx->parts[ctx->i])
		{
			if (!add_from_parts_ctx(ctx, set_fd))
				break ;
		}
		else
		{
			if (!process_regular_word_ctx(ctx, set_fd))
				break ;
		}
		ctx->i = ctx->i + 1;
	}
}

void	expand_argv(t_expand_argv_input in)
{
	t_expand_argv_ctx	ctx;
	char				**old;

	old = *in.argv_ptr;
	ctx.argv = old;
	ctx.new_argv = NULL;
	ctx.split = NULL;
	ctx.quotes = NULL;
	ctx.parts = NULL;
	if (in.quotes_ptr && *in.quotes_ptr)
		ctx.quotes = *in.quotes_ptr;
	if (in.parts_ptr && *in.parts_ptr)
		ctx.parts = *in.parts_ptr;
	ctx.expanded = NULL;
	ctx.total = 0;
	ctx.idx = 0;
	ctx.i = 0;
	ctx.j = 0;
	ctx.env = resolve_envp(in.newenv);
	ctx.cap = 0;
	process_each_arg_ctx(&ctx, in.set_fd);
	if (ensure_cap(&ctx.new_argv, &ctx.cap, ctx.idx + 1))
		ctx.new_argv[ctx.idx] = NULL;
	free_str_array(old);
	*in.argv_ptr = ctx.new_argv;
}
