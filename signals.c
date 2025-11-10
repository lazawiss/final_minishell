/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 23:21:13 by lzannis           #+#    #+#             */
/*   Updated: 2025/10/13 23:32:05 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	setup_signals_fork(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_DFL);
}

void	check_g_sig(t_set_fd *set_fd)
{
	if (g_sig == 130)
		set_fd->last_exit_status = 130;
}

// void	setup_signals_heredoc(void)
// {
// 	sigaction(SIGINT,  &old_sigint, NULL);
// 	sigaction(SIGQUIT, &old_sigquit, NULL);
// }

void	install_heredoc_signals(void)
{
	struct sigaction	old_sigint;
	struct sigaction	old_sigquit;
	struct sigaction	sa;

	sa.sa_handler = sigint_handler_heredoc;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, &old_sigint);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, &old_sigquit);
}
