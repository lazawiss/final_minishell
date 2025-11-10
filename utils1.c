/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 22:17:46 by lzannis           #+#    #+#             */
/*   Updated: 2025/10/11 01:43:10 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// use ft_putstr_fd instead
void	ft_puterr(const char *msg)
{
	if (msg)
		write(2, msg, ft_strlen(msg));
}

void	ft_putmsg(const char *msg)
{
	if (msg)
		write(2, msg, ft_strlen(msg));
}

bool	check_is_a_builtin(char **str)
{
	if (str == NULL)
		return (false);
	return (ft_strcmp(str[0], "echo") == 0 \
	|| ft_strcmp(str[0], "pwd") == 0 \
	|| ft_strcmp(str[0], "cd") == 0 \
	|| ft_strcmp(str[0], "export") == 0 \
	|| ft_strcmp(str[0], "unset") == 0 \
	|| ft_strcmp(str[0], "env") == 0 \
	|| ft_strcmp(str[0], "exit") == 0);
}

void	for_errors(void)
{
	rl_clear_history();
	write(STDERR_FILENO, "Error\n", 6);
	exit(EXIT_FAILURE);
}
