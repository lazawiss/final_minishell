/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:51:00 by lzannis           #+#    #+#             */
/*   Updated: 2025/07/11 15:28:21 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strcpy(char *a, const char *b)
{
	int	i;

	i = 0;
	while (b[i])
	{
		a[i] = b[i];
		i++;
	}
	a[i] = '\0';
	return (a);
}

// #include <assert.h>
// #include <unistd.h>
// #include <string.h>
// int	main(void)
// {
// 	char src[] = "hello";
// 	char dest[15] = "hi...........";
// 	char *p;

// 	p = ft_strcpy(dest, src);
// 	assert(p);
// 	assert(p == dest);
// 	assert(strcmp(dest, src) == 0);
// 	write(1, "OK", 2);
// }