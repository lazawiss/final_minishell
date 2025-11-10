/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 23:47:43 by lzannis           #+#    #+#             */
/*   Updated: 2025/10/16 04:48:32 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	if (g_sig == 0 || g_sig == 130)
	{
		g_sig = 130;
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sigint_handler_heredoc(int sig)
{
	(void)sig;
	if (g_sig == 2 || g_sig == 130)
	{
		g_sig = 130;
		write(STDOUT_FILENO, "\n", 1);
	}
}
