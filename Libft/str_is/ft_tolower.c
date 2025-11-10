/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:20:34 by lzannis           #+#    #+#             */
/*   Updated: 2025/05/30 14:14:14 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}
/*
#include <stdio.h>

int	main(void)
{
	int	c = 88;
	char character = (char) c;
	unsigned char decimal = (unsigned char) c;
	printf("The lower case of c is %d\n", ft_tolower(c));
	printf("Original character of c is %c\n", character);
	printf("Lowercase of c is %c\n", ft_tolower(character));
	printf("The original code ascii of c is %u\n", decimal);
	printf("The real function gives %d\n", ft_tolower(c));
	return (0);
}*/
