/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 00:08:05 by leazannis         #+#    #+#             */
/*   Updated: 2025/10/13 23:26:50 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	is_a_builtin_2(t_ASTNode *node, char ***envp, t_set_fd *set_fd)
{
	if (ft_strcmp(node->argv[0], "export") == 0)
	{
		set_fd->last_exit_status = ft_export(ft_count_args(node->argv),
				node->argv, set_fd, envp);
		return ;
	}
	else if (ft_strcmp(node->argv[0], "unset") == 0)
	{
		set_fd->last_exit_status = ft_unset(ft_count_args(node->argv),
				node->argv, envp);
		return ;
	}
	else if (ft_strcmp(node->argv[0], "env") == 0)
	{
		set_fd->last_exit_status = ft_env(ft_count_args(node->argv), *envp);
		return ;
	}
	else if (ft_strcmp(node->argv[0], "exit") == 0)
	{
		set_fd->last_exit_status = ft_exit(ft_count_args(node->argv),
				node->argv, set_fd, envp);
		return ;
	}
}

void	is_a_builtin(t_ASTNode *node, char ***envp, t_set_fd *set_fd)
{
	if (!node)
		return ;
	if (!node->argv || !node->argv[0])
		return ;
	if (ft_strcmp(node->argv[0], "echo") == 0)
	{
		set_fd->last_exit_status = ft_echo(ft_count_args(node->argv),
				node->argv, set_fd);
		return ;
	}
	else if (ft_strcmp(node->argv[0], "pwd") == 0)
	{
		set_fd->last_exit_status = ft_pwd(set_fd);
		return ;
	}
	else if (ft_strcmp(node->argv[0], "cd") == 0)
	{
		set_fd->last_exit_status = ft_cd(node->argv, envp, set_fd);
		return ;
	}
	else
	{
		is_a_builtin_2(node, envp, set_fd);
		return ;
	}
}
