/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_utils1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 19:53:43 by lzannis           #+#    #+#             */
/*   Updated: 2025/10/16 20:16:35 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*display_tok_text(t_Token *t)
{
	if (!t || t->type == TOKEN_EOF)
		return ("newline");
	if (t->text)
		return (t->text);
	else
		return ("");
}

int	is_directory(const char *path)
{
	struct stat	st;

	return (stat(path, &st) == 0 && S_ISDIR(st.st_mode));
}

bool	is_pipe(t_TknType t)
{
	return (t == TOKEN_PIPE);
}
