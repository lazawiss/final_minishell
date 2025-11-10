/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imirzaev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 22:10:16 by imirzaev          #+#    #+#             */
/*   Updated: 2025/09/28 22:13:02 by imirzaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(t_set_fd *set_fd)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd");
		kill_command(set_fd);
		return (1);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}

void	update_pwd(char ***envp, const char *cwd)
{
	char	*line;
	size_t	len_pwd;
	size_t	len_cwd;

	if (!cwd)
		return ;
	len_pwd = 4;
	len_cwd = ft_strlen(cwd);
	line = (char *)malloc(len_pwd + len_cwd + 1);
	if (!line)
		return ;
	line[0] = 'P';
	line[1] = 'W';
	line[2] = 'D';
	line[3] = '=';
	ft_memcpy(line + 4, cwd, len_cwd);
	line[4 + len_cwd] = '\0';
	if (replace_or_add_var(envp, line, 3) != 0)
	{
		free(line);
		return ;
	}
	free(line);
}
