/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 01:52:06 by lzannis           #+#    #+#             */
/*   Updated: 2025/06/18 01:52:08 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned int	i;

	i = 0;
	c %= 256;
	while (s[i])
		i++;
	if (c == '\0')
		return ((char *)&s[i]);
	while (i > 0 && s[i] != (char)c)
		i--;
	if (c != s[i])
		return (0);
	else
		return ((char *)&s[i]);
}
/*
#include <stdio.h>

void	test( char *s, int c)
{
	printf(" ma fct %s | ", ft_strrchr(s, c));
	printf("la vraie %s\n", strrchr(s, c));
}

int	main(void)
{
	test("",'\0');
	test("",'t');
    test("a", '\0');
    test("test",'t');
    test("test", 't' + 256);
    test("test", 'e');
	test("teste", 'e');
    test("test", 'a');
    test("test", 'a' + 256);
    test("test5", '5');
    test("test5", '5' + 256);
	return (0);
}*/