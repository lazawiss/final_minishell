/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 22:08:30 by imirzaev          #+#    #+#             */
/*   Updated: 2025/10/16 23:38:31 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	try_replace_existing_var(t_env_st *st, const char *arg, size_t namelen)
{
	(void)namelen;
	st->j = 0;
	while (st->env && st->env[st->j])
	{
		if (!ft_strncmp(st->env[st->j], arg, namelen)
			&& (st->env[st->j][namelen] == '='
			|| st->env[st->j][namelen] == '\0'))
		{
			st->dup = ft_strdup(arg);
			if (!st->dup)
				return (1);
			free(st->env[st->j]);
			st->env[st->j] = st->dup;
			return (0);
		}
		st->j++;
	}
	return (-1);
}

int	is_valid_identifier(const char *s)
{
	int	i;

	if (!s || !*s)
		return (0);
	if (!ft_isalpha((unsigned char)*s) && *s != '_')
		return (0);
	i = 1;
	while (s[i] && s[i] != '=')
	{
		if (!ft_isalnum((unsigned char)s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

char	**allocate_new_env(t_env_st *st)
{
	char	**newv;

	newv = (char **)malloc(sizeof(char *) * (st->count + 2));
	if (!newv)
		return (NULL);
	st->j = 0;
	while (st->j < st->count)
	{
		newv[st->j] = ft_strdup(st->env[st->j]);
		if (!newv[st->j])
		{
			while (st->j > 0)
			{
				st->j--;
				free(newv[st->j]);
			}
			free(newv);
			return (NULL);
		}
		st->j++;
	}
	newv[st->count] = NULL;
	newv[st->count + 1] = NULL;
	return (newv);
}

static int	append_new_var(char ***envp, const char *arg, size_t namelen)
{
	t_env_st	st;

	(void)namelen;
	st.env = *envp;
	st.count = 0;
	while (st.env && st.env[st.count])
		st.count++;
	st.newv = allocate_new_env(&st);
	if (!st.newv)
		return (1);
	st.dup = ft_strdup(arg);
	if (!st.dup)
	{
		while (st.count--)
			free(st.newv[st.count]);
		free(st.newv);
		return (1);
	}
	st.newv[st.count] = st.dup;
	st.newv[st.count + 1] = NULL;
	if (st.env)
		ft_free(st.env);
	*envp = st.newv;
	return (0);
}

int	replace_or_add_var(char ***envp, const char *arg, size_t namelen)
{
	t_env_st	st;

	st.env = *envp;
	st.res = try_replace_existing_var(&st, arg, namelen);
	if (st.res != -1)
		return (st.res);
	return (append_new_var(envp, arg, namelen));
}
