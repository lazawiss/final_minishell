/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 23:32:14 by lzannis           #+#    #+#             */
/*   Updated: 2025/05/30 13:54:52 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (8);
	return (0);
}
/*
#include <stdio.h>
#include <ctype.h>

int	main(void)
{
	int	c = 75;
	char 	alphanum = (char) c;
	char unsigned decimal = (char unsigned) c;
	printf("Is c an alpha numeric? %d\n", ft_isalnum(c));
	printf("What character is c? %c\n", alphanum);
	printf("Which code ASCII is c? %u\n", decimal);
	printf("The real funcion ? %d\n", isalnum(c));
	return (0);
}*/
