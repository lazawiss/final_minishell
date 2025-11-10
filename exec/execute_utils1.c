/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:38:17 by lzannis           #+#    #+#             */
/*   Updated: 2025/10/17 00:21:40 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_value(char **env, const char *name)
{
	size_t	len;
	int		i;

	i = 0;
	if (!env || !name || !*name)
		return (NULL);
	len = ft_strlen(name);
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

void	free_and_exit(t_ASTNode *tmp)
{
	if (tmp)
		free_ast(tmp);
	exit(EXIT_FAILURE);
}

void	kill_command(t_set_fd *set_fd)
{
	if (set_fd)
		free_set_fd(set_fd);
	return ;
}

bool	close_node_pipe(t_set_fd *set_fd, char ***newenv)
{
	if (set_fd->arrpid)
		awaiting_children(set_fd, set_fd->arrpid);
	g_sig = 0;
	if (!close_file(&set_fd->infile_fd, &set_fd->outfile_fd))
	{
		close_safe(set_fd, newenv);
		return (false);
	}
	return (true);
}

bool	exec_simple_without_pipe(t_ASTNode *tmp, \
	t_set_fd *set_fd, char ***newenv)
{
	if (!exec_single(tmp, set_fd, newenv))
	{
		if (!close_exec_simple(set_fd, newenv))
			return (false);
		return (false);
	}
	if (!close_exec_simple(set_fd, newenv))
		return (false);
	return (true);
}
