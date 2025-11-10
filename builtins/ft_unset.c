/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 22:13:19 by imirzaev          #+#    #+#             */
/*   Updated: 2025/10/17 00:23:42 by imirzaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	match_env_var(const char *env_entry,
		const char *name, size_t name_len)
{
	if (ft_strncmp(env_entry, name, name_len) == 0)
	{
		if (env_entry[name_len] == '\0' || env_entry[name_len] == '=')
			return (1);
	}
	return (0);
}

static void	shift_env_vars(char **env, int start)
{
	int	w;

	w = start;
	while (env[w])
	{
		env[w] = env[w + 1];
		w++;
	}
}

static int	remove_var(char ***envp, const char *name)
{
	char	**env;
	int		j;
	size_t	name_len;

	env = *envp;
	if (!*envp || !name)
		return (0);
	name_len = ft_strlen(name);
	j = 0;
	while (env[j])
	{
		if (match_env_var(env[j], name, name_len))
		{
			free(env[j]);
			shift_env_vars(env, j);
			return (0);
		}
		j++;
	}
	return (0);
}

int	ft_unset(int argc, char **argv, char ***envp)
{
	int		i;
	char	*name;

	i = 1;
	while (i < argc)
	{
		name = argv[i];
		if (!name || !*name || ft_strchr(name, '=')
			|| !is_valid_identifier(name))
		{
			ft_puterr("minish-elles: unset: `");
			ft_puterr(name);
			ft_puterr("': not a valid identifier\n");
			return (1);
		}
		remove_var(envp, name);
		i++;
	}
	return (0);
}
