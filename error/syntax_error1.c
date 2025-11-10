/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 18:00:14 by lzannis           #+#    #+#             */
/*   Updated: 2025/10/16 21:58:34 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	msg_directory(t_set_fd *set_fd, char *cmd, char ***newenv)
{
	ft_putstr_fd("minish-elles: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": Is a directory", 2);
	free_builtins(set_fd, newenv);
	set_fd->last_exit_status = 126;
	exit(126);
}

void	msg_eaccess(t_set_fd *set_fd, char *cmd, char ***newenv)
{
	ft_putstr_fd("minish-elles: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": Permission denied", 2);
	free_builtins(set_fd, newenv);
	set_fd->last_exit_status = 126;
	exit(126);
}

void	msg_enoent(t_set_fd *set_fd, char *cmd, char ***newenv)
{
	ft_putstr_fd("minish-elles: ", 2);
	ft_putstr_fd(cmd, 2);
	if (ft_strchr(cmd, '/') || set_fd->no_env)
		ft_putendl_fd(": No such file or directory SYNTAX ERROR", 2);
	else
		ft_putendl_fd(": command not found", 2);
	free_builtins(set_fd, newenv);
	set_fd->last_exit_status = 127;
	exit(127);
}

void	msg_strerror(int e, t_set_fd *set_fd, char *cmd, char ***newenv)
{
	ft_putstr_fd("minish-elles: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(e), 2);
	free_builtins(set_fd, newenv);
	set_fd->last_exit_status = 127;
	exit(127);
}

void	exec_error_handler(t_set_fd *set_fd, char *cmd, char ***newenv)
{
	int	e;

	e = errno;
	close_pipe(set_fd->next_pipe);
	close_pipe(set_fd->prev_pipe);
	if (is_directory(cmd))
		msg_directory(set_fd, cmd, newenv);
	else if (e == EACCES)
		msg_eaccess(set_fd, cmd, newenv);
	else if (e == ENOENT || set_fd->no_env)
		msg_enoent(set_fd, cmd, newenv);
	else
		msg_strerror(e, set_fd, cmd, newenv);
}
