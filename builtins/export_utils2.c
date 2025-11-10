/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imirzaev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 00:26:43 by imirzaev          #+#    #+#             */
/*   Updated: 2025/10/17 00:26:45 by imirzaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	get_name_len_no_equal(const char *name)
{
	size_t	len;

	len = 0;
	while (name[len] && name[len] != '=')
		len++;
	return (len);
}

int	update_existing_no_value(char **env, const char *name, size_t namelen)
{
	char	*with_eq;	

	if (env[namelen] == NULL)
	{
		with_eq = malloc(namelen + 2);
		if (!with_eq)
			return (1);
		ft_memcpy(with_eq, name, namelen);
		with_eq[namelen] = '=';
		with_eq[namelen + 1] = '\0';
		free(*env);
		*env = with_eq;
	}
	return (0);
}

int	append_empty_assignment(char ***envp, const char *name, size_t namelen)
{
	char	*with_eq;
	int		ret;	

	with_eq = malloc(namelen + 2);
	if (!with_eq)
		return (1);
	ft_memcpy(with_eq, name, namelen);
	with_eq[namelen] = '=';
	with_eq[namelen + 1] = '\0';
	ret = replace_or_add_var(envp, with_eq, namelen);
	free(with_eq);
	return (ret);
}
