/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 00:57:37 by lzannis           #+#    #+#             */
/*   Updated: 2025/06/18 00:57:41 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	is_a_set(char const *set, int c)
{
	while (*set)
	{
		if (*set == (char)c)
			return (1);
		set++;
	}
	return (0);
}

static char	*ft_strncpy(char *dest, char const *src, size_t n, size_t start)
{
	size_t	i;

	i = 0;
	while (src[start] && start < n)
	{
		dest[i] = src[start];
		i++;
		start++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*ptr;
	unsigned int	start;
	unsigned int	end;

	if (!s1)
		return (ft_strdup(""));
	if (!set)
		return ((char *)s1);
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && (is_a_set(set, s1[start]) == 1))
		start++;
	while (start < end && (is_a_set(set, s1[end - 1]) == 1))
		end--;
	ptr = (char *)malloc (sizeof(char) * (end - start) + 1);
	if (!ptr)
		return (NULL);
	ft_strncpy(ptr, s1, end, start);
	return (ptr);
}
/*
int	main(void)
{
	char	a[] = ", -yb!!!he aaargjaeuga-aawefhhh5b-:;";
	char set[] = ", -:;";
	char *b = ft_strtrim(a,set);
	printf("chaine a :%s | ",a);
	printf("chaine b :%s\n",b);
	if (*b)
		free(b);
	return (0 );
}*/
