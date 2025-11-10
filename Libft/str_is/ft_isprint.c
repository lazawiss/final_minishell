/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 00:26:04 by lzannis           #+#    #+#             */
/*   Updated: 2025/05/30 14:14:52 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_isprint(int c)
{
	if (!((c <= 31) || c > 126))
		return (16384);
	return (0);
}
/*
#include <stdio.h>

int	main(void)
{
	int	c = -1;
	char	character = (char) c;
	unsigned char decimal = (unsigned char) c;
	printf("Is c printable? %d\n", ft_isprint(c));
	printf("Which character is c? %c\n", character);
	printf("Which ASCII code is c? %u\n", decimal);
	printf("The real function : %d\n", isprint(c));
	return (0);
}*/
