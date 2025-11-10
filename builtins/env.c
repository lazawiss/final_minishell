/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:57:29 by leazannis         #+#    #+#             */
/*   Updated: 2025/10/16 23:31:00 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_newenv(char **newenv, char **env)
{
	int	i;
	int	count;

	if (!env || !env[0])
		return (NULL);
	count = 0;
	while (env[count])
		count++;
	newenv = (char **)malloc(sizeof(char *) * (count + 1));
	if (!newenv)
		return (NULL);
	i = -1;
	while (++i < count)
	{
		newenv[i] = ft_strdup(env[i]);
		if (!newenv[i])
		{
			while (--i >= 0)
				free(newenv[i]);
			free(newenv);
			return (NULL);
		}
	}
	newenv[count] = NULL;
	return (newenv);
}

static int	has_equal(const char *s)
{
	while (*s && *s != '=')
		s++;
	return (*s == '=');
}

void	print_env(char **envp)
{
	int	i;

	if (!envp)
	{
		return ;
	}
	i = 0;
	while (envp[i])
	{
		if (has_equal(envp[i]))
		{
			ft_putendl_fd(envp[i], 1);
		}
		i++;
	}
}

int	ft_env(int argc, char **envp)
{
	if (argc > 1)
	{
		write(2, "minishell: env: too many arguments\n", 36);
		return (1);
	}
	print_env(envp);
	return (0);
}
