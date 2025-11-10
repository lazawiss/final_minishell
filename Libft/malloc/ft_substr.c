/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 01:17:47 by lzannis           #+#    #+#             */
/*   Updated: 2025/10/13 23:07:28 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// if (start > ft_strlen(s))
// 	return (ft_strdup(""));
// if (start + len > ft_strlen(s))
// 	len = ft_strlen(s) - start;

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	char	*ptr;
// 	size_t	slen;

// 	if (!s)
// 		return (NULL);
// 	slen = ft_strlen(s);
// 	if (start >= slen)
// 		return (ft_calloc(1, 1));
// 	if (len > slen - start)
// 		len = slen - start;
// 	ptr = malloc(len + 1);
// 	if (!ptr)
// 		return (NULL);
// 	ft_memcpy(ptr, s + start, len);
// 	ptr[len] = '\0';
// 	return (ptr);
// }

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	j;

	if (!s)
		return (NULL);
	j = 0;
	ptr = (char *)malloc ((len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	while (j < len)
	{
		ptr[j] = s[start + j];
		j++;
	}
	ptr[j] = '\0';
	return (ptr);
}
/*
int	main(void)
{
	printf("%s\n", ft_substr("bonjour", 2, 2));


}*/