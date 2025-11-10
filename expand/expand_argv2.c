/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_argv2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imirzaev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 22:54:44 by imirzaev          #+#    #+#             */
/*   Updated: 2025/10/16 23:04:16 by imirzaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	allocate_new_block(char ***arr, int old_cap, int *new_cap, int need)
{
	char	**new_block;
	int		i;

	if (old_cap == 0)
		*new_cap = 4;
	else
		*new_cap = old_cap;
	while (*new_cap < need)
		*new_cap *= 2;
	new_block = (char **)malloc(sizeof(char *) * (*new_cap + 1));
	if (!new_block)
		return (0);
	i = 0;
	while (i <= *new_cap)
	{
		new_block[i] = NULL;
		i++;
	}
	*arr = new_block;
	return (1);
}

int	ensure_cap(char ***arr, int *cap, int need)
{
	char	**new_block;
	int		newcap;
	int		i;

	if (need <= *cap)
		return (1);
	new_block = *arr;
	if (!allocate_new_block(&new_block, *cap, &newcap, need))
		return (0);
	if (*arr)
	{
		i = 0;
		while (i < *cap)
		{
			new_block[i] = (*arr)[i];
			i++;
		}
		free(*arr);
	}
	*arr = new_block;
	*cap = newcap;
	return (1);
}

char	*expand_part(t_wordpart *part, t_set_fd *set_fd, char **envp)
{
	char	*merged;

	merged = expand_from_parts(part, set_fd, envp);
	if (!merged)
	{
		merged = ft_strdup("");
		if (!merged)
			return (NULL);
	}
	return (merged);
}

char	**resolve_envp(char ***newenv)
{
	if (newenv && *newenv)
		return (*newenv);
	return (NULL);
}

int	add_from_parts_ctx(t_expand_argv_ctx *ctx, t_set_fd *set_fd)
{
	char	*merged;

	merged = expand_from_parts(ctx->parts[ctx->i], set_fd, ctx->env);
	if (!merged)
	{
		merged = ft_strdup("");
		if (!merged)
			return (0);
	}
	if (!ensure_cap(&ctx->new_argv, &ctx->cap, ctx->idx + 1))
	{
		free(merged);
		return (0);
	}
	ctx->new_argv[ctx->idx] = merged;
	ctx->idx = ctx->idx + 1;
	return (1);
}
