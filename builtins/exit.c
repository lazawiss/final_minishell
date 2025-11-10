/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 22:06:40 by imirzaev          #+#    #+#             */
/*   Updated: 2025/10/16 00:37:01 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_numeric(const char *s)
{
	if (!s || !*s)
		return (0);
	if (*s == '+' || *s == '-')
		s++;
	while (*s)
	{
		if (!ft_isdigit((unsigned char)*s))
			return (0);
		s++;
	}
	return (1);
}

static int	is_overflow(char *str)
{
	double	validd;
	int		validi;

	validd = ft_atol(str);
	validi = ft_atoi(str);
	if (*str == '-' && ft_strlen(str) > 11)
		return (1);
	else if (*str != '-' && ft_strlen(str) > 10)
		return (1);
	if (validd != validi)
		return (1);
	return (0);
}

void	msg_exit(char *tok)
{
	ft_putstr_fd("minish-elles: exit:", 2);
	ft_putstr_fd(tok, 2);
	ft_putendl_fd(": numeric argument required", 2);
}

int	ft_exit(int argc, char **argv, t_set_fd *set_fd, char ***envp)
{
	unsigned char	code;

	if (g_sig != 1)
		write(1, "exit\n", 6);
	if (argc == 1)
	{
		free_all(NULL, set_fd, envp);
		exit(set_fd->last_exit_status);
	}
	if (!is_numeric(argv[1]) || is_overflow(argv[1]) == 1)
	{
		msg_exit(argv[1]);
		free_all(NULL, set_fd, envp);
		exit(2);
	}
	if (argc > 2)
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	code = (unsigned char)ft_atoi(argv[1]);
	free_all(NULL, set_fd, envp);
	exit(code);
}
