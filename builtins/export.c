/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 22:07:28 by imirzaev          #+#    #+#             */
/*   Updated: 2025/10/16 23:53:50 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	add_name_without_value(char ***envp, const char *name)
{
	char	**env;
	size_t	namelen;
	int		j;

	if (!name || !*name)
		return (1);
	namelen = get_name_len_no_equal(name);
	env = *envp;
	j = 0;
	while (env && env[j])
	{
		if (!ft_strncmp(env[j], name, namelen)
			&& (env[j][namelen] == '=' || env[j][namelen] == '\0'))
			return (update_existing_no_value(&env[j], name, namelen));
		j++;
	}
	return (append_empty_assignment(envp, name, namelen));
}

int	validate_and_prepare_name(char *arg, t_set_fd *set_fd, size_t namelen)
{
	char	*name;

	name = ft_substr(arg, 0, namelen);
	if (!name)
		return (1);
	if (!is_valid_identifier(name))
	{
		ft_putstr_fd("minish-elles: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		free(name);
		set_fd->last_exit_status = 1;
		return (1);
	}
	free(name);
	return (0);
}

int	handle_export_with_value(char *arg,
	t_set_fd *set_fd, char ***envp)
{
	size_t	namelen;
	char	*eq;

	eq = ft_strchr(arg, '=');
	if (!eq)
		return (0);
	namelen = (size_t)(eq - arg);
	if (validate_and_prepare_name(arg, set_fd, namelen))
		return (1);
	return (replace_or_add_var(envp, arg, namelen));
}

int	handle_export_without_value(char *arg,
	t_set_fd *set_fd, char ***envp)
{
	if (!is_valid_identifier(arg))
	{
		ft_putstr_fd("minish-elles: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		set_fd->last_exit_status = 1;
		return (1);
	}
	return (add_name_without_value(envp, arg));
}

int	ft_export(int argc, char **argv,
	t_set_fd *set_fd, char ***envp)
{
	int	i;
	int	ret;

	if (argc == 1)
	{
		print_env(*envp);
		return (0);
	}
	i = 1;
	while (i < argc)
	{
		if (ft_strchr(argv[i], '='))
			ret = handle_export_with_value(argv[i], set_fd, envp);
		else
			ret = handle_export_without_value(argv[i], set_fd, envp);
		if (ret != 0)
			return (ret);
		i++;
	}
	return (0);
}
