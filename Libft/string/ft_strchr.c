/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 01:39:37 by lzannis           #+#    #+#             */
/*   Updated: 2025/06/18 02:04:25 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strchr(const char *s, int c)
{
	c %= 256;
	while (*(char *)s)
	{
		if (*(char *)s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	else
		return (0);
}
/*
#include <stdio.h> 

void    test(char *str, int c)
{
     printf("ma fonction :%s | ", ft_strchr(str, c));
     printf("la vraie fonction : %s\n", strchr(str,c));
}
 
int main(void)
{
     test("",'\0');
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