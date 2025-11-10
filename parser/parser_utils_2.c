/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 01:16:30 by imirzaev          #+#    #+#             */
/*   Updated: 2025/10/13 18:16:18 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_ASTNode	*parse_and_or(t_Parser *p)
{
	t_ASTNode	*left;

	left = parse_pipeline(p);
	if (!left)
		return (NULL);
	return (left);
}

t_ASTNode	*parse_expression(t_Parser *p)
{
	return (parse_sequence(p));
}

t_ASTNode	*parse(t_Token *tokens)
{
	t_Parser	p;

	p.current = tokens;
	p.val = 0;
	p.argv_count = 0;
	return (parse_expression(&p));
}
