/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 23:50:34 by lzannis           #+#    #+#             */
/*   Updated: 2025/10/16 20:19:11 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	msg_is_logic_or_pipe(t_set_fd *set_fd, t_Token *tok)
{
	ft_putstr_fd("minish-elles: syntax error near unexpected token `", 2);
	if (tok->type == TOKEN_PIPE && tok->next->type == TOKEN_PIPE)
		ft_putstr_fd("||", 2);
	else
		ft_putstr_fd(display_tok_text(tok), 2);
	ft_putendl_fd("'", 2);
	set_fd->last_exit_status = 2;
}

void	msg_is_redir_word(t_set_fd *set_fd, t_Token *tok)
{
	ft_putstr_fd("minish-elles: syntax error near unexpected token `", 2);
	ft_putstr_fd(display_tok_text(tok->next), 2);
	ft_putendl_fd("'", 2);
	set_fd->last_exit_status = 2;
}

bool	syntax_error_is_logic(t_Token *prev, t_set_fd *set_fd, t_Token *tok)
{
	if (!prev || is_logic(tok) || (!prev && is_logic(tok)))
	{
		msg_is_logic_or_pipe(set_fd, tok);
		return (true);
	}
	if ((!prev && is_pipe(tok->type)) || (is_pipe(tok->type) && !tok->next))
	{
		msg_is_logic_or_pipe(set_fd, tok);
		return (true);
	}
	if (!tok->next || tok->next->type == TOKEN_EOF)
	{
		ft_putendl_fd
		("minish-elles: syntax error near unexpected token `newline'", 2);
		set_fd->last_exit_status = 2;
		return (true);
	}
	return (false);
}

bool	syntax_error_is_redir(t_set_fd *set_fd, t_Token *tok)
{
	if (!tok->next || tok->next->type == TOKEN_EOF)
	{
		ft_putendl_fd
		("minish-elles: syntax error near unexpected token `newline'", 2);
		set_fd->last_exit_status = 2;
		return (true);
	}
	if (tok->next->type != TOKEN_WORD)
	{
		msg_is_redir_word(set_fd, tok);
		return (true);
	}
	return (false);
}

bool	syntax_error(t_set_fd *set_fd, t_Token *tok)
{
	t_Token	*prev;
	t_Token	*cur;

	prev = NULL;
	cur = tok;
	while (cur)
	{
		if (is_logic(cur) || is_pipe(cur->type))
		{
			if (syntax_error_is_logic(prev, set_fd, cur))
				return (free_tokens(tok), true);
		}
		if (is_redirection(cur->type))
		{
			if (syntax_error_is_redir(set_fd, cur))
				return (free_tokens(tok), true);
		}
		prev = cur;
		cur = cur->next;
	}
	return (false);
}
