/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 22:29:47 by lzannis           #+#    #+#             */
/*   Updated: 2025/10/16 00:18:12 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_ASTNode	*search_cmds(t_ASTNode *tmp)
{
	t_ASTNode	*left_result;
	t_ASTNode	*right_result;

	left_result = NULL;
	right_result = NULL;
	if (tmp->type == NODE_COMMAND)
		return (tmp);
	if (tmp == NULL)
		return (NULL);
	if (tmp && tmp->left)
		left_result = search_cmds(tmp->left);
	if (tmp && tmp->right)
		right_result = search_cmds(tmp->right);
	if (left_result)
		return (left_result);
	if (right_result)
		return (right_result);
	return (NULL);
}

char	*cmd_transfert(t_ASTNode *tmp, char *short_path)
{
	if (tmp->cmd1)
		free(tmp->cmd1);
	if (!short_path)
		return (NULL);
	tmp->cmd = ft_strjoin(short_path, "/");
	if (tmp->cmd == NULL)
		return (NULL);
	if (tmp->argv)
	{
		tmp->cmd1 = ft_strjoin(tmp->cmd, tmp->argv[0]);
		if (tmp->cmd1 == NULL)
		{
			free(tmp->cmd);
			free(tmp->argv[0]);
			return (NULL);
		}
	}
	free(tmp->cmd);
	return (tmp->cmd1);
}

char	*check_path(t_ASTNode *node, t_set_fd *set_fd)
{
	char	**short_path;
	int		i;

	i = 0;
	short_path = NULL;
	if (!set_fd->pathname)
	{
		set_fd->no_env = true;
		return (NULL);
	}
	short_path = ft_split(set_fd->pathname, ':');
	if (!short_path)
		return (NULL);
	while (short_path[i])
	{
		cmd_transfert(node, short_path[i]);
		if (access(node->cmd1, F_OK | X_OK) == 0)
		{
			ft_free(short_path);
			return (node->cmd1);
		}	
		i++;
	}
	ft_free(short_path);
	return (NULL);
}

bool	get_path(t_set_fd *set_fd, char **newenv)
{
	int	i;
	int	varlen;
	int	start;	

	i = 0;
	varlen = 0;
	start = 4;
	while (newenv && newenv[i])
	{
		if (ft_strncmp(newenv[i], "PATH=", 5) == 0)
		{
			varlen = ft_strlen(newenv[i]);
			set_fd->pathname = ft_substr(newenv[i], start, varlen - start);
			if (!set_fd->pathname)
				return (false);
		}
		i++;
	}
	return (true);
}

void	init_execute_child(t_set_fd *set_fd)
{
	set_fd->i = 0;
	set_fd->prev_pipe[0] = -1;
	set_fd->prev_pipe[1] = -1;
	set_fd->next_pipe[0] = -1;
	set_fd->next_pipe[1] = -1;
	set_fd->arrpid = malloc(sizeof(pid_t) * set_fd->nbcmds);
	if (!set_fd->arrpid)
		return ;
}
