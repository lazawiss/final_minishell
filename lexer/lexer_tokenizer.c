/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 00:26:21 by imirzaev          #+#    #+#             */
/*   Updated: 2025/10/16 22:52:53 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_Token	*handle_greater(const char **p, t_Token *cur)
{
	if ((*p)[1] == '>')
	{
		cur->next = new_token(cur, TOKEN_REDIR_OUT_APPEND,
				ft_strdup(">>"), QUOTE_NONE);
		*p += 2;
	}
	else
	{
		cur->next = new_token(cur, TOKEN_REDIR_OUT, ft_strdup(">"), QUOTE_NONE);
		(*p)++;
	}
	return (cur->next);
}

t_Token	*handle_less(const char **p, t_Token *cur)
{
	if ((*p)[1] == '<')
	{
		cur->next = new_token(cur, TOKEN_HEREDOC, ft_strdup("<<"), QUOTE_NONE);
		*p += 2;
	}
	else
	{
		cur->next = new_token(cur, TOKEN_REDIR_IN, ft_strdup("<"), QUOTE_NONE);
		(*p)++;
	}
	return (cur->next);
}

t_Token	*handle_operator(const char **p, t_Token *cur)
{
	if (**p == '|')
	{
		cur->next = new_token(cur, TOKEN_PIPE, ft_strdup("|"), QUOTE_NONE);
		(*p)++;
		return (cur->next);
	}
	if (**p == '>')
		return (handle_greater(p, cur));
	if (**p == '<')
		return (handle_less(p, cur));
	return (cur);
}

t_Token	*lexer_tokenize(const char *line)
{
	if (!line)
		return (NULL);
	return (lexer_process_line(line));
}

t_Token	*process_lexer_chunks(const char **p, t_Token *cur, t_Token *head)
{
	while (**p)
	{
		while (ft_is_space_char((unsigned char)**p))
			(*p)++;
		if (!**p)
			break ;
		cur = lexer_process_chunk(p, cur);
		if (!cur)
		{
			free_tokens(head->next);
			return (NULL);
		}
	}
	return (cur);
}
