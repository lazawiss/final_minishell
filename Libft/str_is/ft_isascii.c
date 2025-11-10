/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 23:55:27 by lzannis           #+#    #+#             */
/*   Updated: 2025/05/30 14:13:37 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}
/*
#include <stdio.h>
#include <ctype.h>

int	main(void)
{
	int	c = 55;
	char	character = (char) c;
	unsigned char decimal = (unsigned char) c;
	printf("Is c in the ASCII table? %d\n", ft_isascii(c));
	printf("Which character is c? %c\n", character);
	printf("Which ASCII code is c? %u\n", decimal);
	printf("The real function? %d\n", isascii(c));
	return (0);
}*/
