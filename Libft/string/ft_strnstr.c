/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 01:48:41 by lzannis           #+#    #+#             */
/*   Updated: 2025/06/18 02:04:48 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (*little == '\0')
		return ((char *)big);
	if (*big == '\0')
		return (NULL);
	while (i < len)
	{
		j = 0;
		while (big[i] && big[i + j] == little[j] && (i + j < len))
		{
			if (little[j +1] == '\0')
				return ((char *)&big[i]);
			j++;
		}
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
#include <bsd/string.h>

void	test(char *big, char *little, size_t len)
{
	printf("ma fonction %s | ", ft_strnstr(big, little, len));
	printf("la vraie fonction %s\n", strnstr(big, little, len));
}

int	main(void)
{
	test("hello", "lo", 0);
	test("hello", "lo", 1);
	test("hello", "lo", 2);
	test("hello", "lo", 3);
	test("hello", "lo", 4);
	test("hello", "lo", 5);
	test("hello", "", 5);
	test("hello", "do", 5);
	test("hello", "llo", 5);
	test("", "", 5);
	test("", "", 0);
	test("lorem ipsum dolor sit amet", "lorem", 15);



}

const char *haystack;
    const char *needle;

    if (!*little)
        return ((char *)big);
    while (*big)
    {
        haystack = big;
        needle = little;
        while (*haystack && *needle)
        {
            if (*haystack != *needle)
                break;
            haystack++;
            needle++;
            len--;
        }
        if (!*needle)
            return ((char*)big);
        big++;
    }
    return (0);*/