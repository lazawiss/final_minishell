/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leazannis <leazannis@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 01:27:15 by lzannis           #+#    #+#             */
/*   Updated: 2025/08/21 00:19:37 by leazannis        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_wordlen(const char *str, char set, int start)
{
	int	i;

	i = start;
	while (str[i] && str[i] != set)
		i++;
	return (i - start);
}

int	ft_count_word(const char *str, char set)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (str[i])
	{
		if (str[i] == set)
			word++;
		while (str[i] != set)
		{
			if (str[i + 1] == set || str[i + 1] == '\0')
			{
				word++;
				break ;
			}
			i++;
		}
		i++;
	}
	return (word);
}

static char	*ft_substr_split(const char *str, int start, int len)
{
	char	*ptr;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	ptr = ft_calloc((len + 1), sizeof(char));
	if (!ptr)
		return (NULL);
	while (str && str[start] && (i < len))
	{
		ptr[i] = str[start];
		i++;
		start++;
	}
	ptr[i] = '\0';
	return (ptr);
}

static void	ft_innit_split(const char *str, char set, t_split *s)
{
	s->i = 0;
	s->count_word = ft_count_word(str, set);
	s->ptr = ft_calloc(sizeof(char *), s->count_word + 1);
	if (!s->ptr)
		exit(1);
}

char	**ft_split(char const *str, char set)
{
	t_split	local;

	ft_memset(&local, 0, sizeof(t_split));
	ft_innit_split(str, set, &local);
	while (str && str[local.i] && local.count_word != 0)
	{
		while (str[local.i] == set)
			local.i++;
		if (str[local.i] && str[local.i] != set)
		{
			local.len = ft_wordlen(str, set, local.i);
			local.ptr[local.x] = ft_substr_split(str, local.i, local.len);
			if (!local.ptr[local.x])
			{
				ft_free(local.ptr);
				return (NULL);
			}
			local.x++;
			local.i += local.len;
			if (local.i >= ft_strlen(str))
				break ;
		}
	}
	local.ptr[local.x] = NULL;
	return (local.ptr);
}
