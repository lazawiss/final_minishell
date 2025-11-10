/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_unquoted.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 17:00:59 by imirzaev          #+#    #+#             */
/*   Updated: 2025/10/10 14:43:45 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_words_unquoted(const char *s)
{
	const char	*p;
	int			count;

	p = s;
	count = 0;
	while (*p)
	{
		while (*p && ft_is_space_char((unsigned char)*p))
			p++;
		if (!*p)
			break ;
		count++;
		while (*p && !ft_is_space_char((unsigned char)*p))
			p++;
	}
	return (count);
}

static char	**allocate_result_array(int count)
{
	char	**result;
	int		i;

	i = 0;
	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		exit(1);
	while (i <= count)
	{
		result[i] = NULL;
		i++;
	}
	return (result);
}

static void	fill_words_unquoted(char **result, const char *s)
{
	const char	*p;
	const char	*start;
	int			idx;

	p = s;
	idx = 0;
	while (*p)
	{
		while (*p && ft_is_space_char((unsigned char)*p))
			p++;
		if (!*p)
			break ;
		start = p;
		while (*p && !ft_is_space_char((unsigned char)*p))
			p++;
		result[idx] = ft_substr(start, 0, p - start);
		if (!result[idx])
		{
			printf("NO RESULT\n");
			exit(1);
		}
		idx++;
	}
	result[idx] = NULL;
}

char	**split_unquoted(const char *s)
{
	int		count;
	char	**result;

	if (!s)
		return (NULL);
	count = count_words_unquoted(s);
	result = allocate_result_array(count);
	fill_words_unquoted(result, s);
	return (result);
}
