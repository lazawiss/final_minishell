/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 22:09:23 by imirzaev          #+#    #+#             */
/*   Updated: 2025/10/16 23:46:51 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	cd_change_directory(char **argv, char ***envp, t_set_fd *set_fd)
{
	const char	*path;

	if (argv[1] && argv[2])
	{
		ft_putendl_fd("minish-elles: cd: too many arguments", 2);
		set_fd->last_exit_status = 1;
		return (1);
	}
	if (!argv[1])
	{
		path = get_env_value(*envp, "HOME");
		if (!path)
		{
			write(2, "minishell: cd: HOME not set\n", 29);
			return (1);
		}
	}
	else
		path = argv[1];
	if (chdir(path) != 0)
	{
		perror("minishell: cd");
		return (1);
	}
	return (0);
}

bool	ft_cd(char **argv, char ***envp, t_set_fd *set_fd)
{
	char	*cwd;

	if (cd_change_directory(argv, envp, set_fd) != 0)
		return (1);
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		update_pwd(envp, cwd);
		free(cwd);
	}
	return (0);
}
