/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 19:30:33 by lzannis           #+#    #+#             */
/*   Updated: 2025/10/16 21:22:39 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_logic(t_Token *t)
{
	if ((t->type == TOKEN_PIPE && t->next->type == TOKEN_PIPE))
		return (true);
	if (ft_strcmp(t->text, "&") == 0 || ft_strcmp(t->text, "&&") == 0)
		return (true);
	return (false);
}

bool	is_redirection(t_TknType t)
{
	return (t == TOKEN_REDIR_OUT \
	|| t == TOKEN_REDIR_OUT_APPEND \
	|| t == TOKEN_REDIR_IN \
	|| t == TOKEN_HEREDOC);
}

void	ft_puterr_token(char *msg, char *tok)
{
	ft_putstr_fd("minish-elles: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(" `", 2);
	ft_putstr_fd(tok, 2);
	ft_putendl_fd("'", 2);
}

void	ft_puterr_cmd_not_fnd(void)
{
	ft_putendl_fd("minish-elles: : command not found", 2);
}

void	ft_puterr_cmd_not_fnd_tok(char *tok)
{
	ft_putstr_fd("minish-elles: ", 2);
	ft_putstr_fd(tok, 2);
	ft_putendl_fd(": command not found", 2);
}
