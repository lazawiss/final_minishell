/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:13:30 by lzannis           #+#    #+#             */
/*   Updated: 2025/10/13 23:05:56 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	number;

	i = 0;
	sign = 1;
	number = 0;
	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == 32)
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(nptr[i]))
	{
		number = (number * 10) + (nptr[i] - '0');
		i++;
	}
	return (number * sign);
}
/*
#include <stdio.h>

void	test(char *str, char *stra)
{
	printf("ma fonction %d | ", ft_atoi(str));
	printf("la vraie fonction %d\n", atoi(stra));
}

int	main(void)
{
	test("","");
	test("0","0");
	test(" \t-0"," \t-0");
	test("      7584jgf","      7584jgf");
	test("\v+++855","\v+++855");
	test("\r+527102548yyr","\r+527102548yyr");
	test("\futdfe7782","\futdfe7782");
	test("  -87269222108875","  -87269222108875");
	test("    -+785412jjg", "    -+785412jjg");
	test("  -2147483648", "  -2147483648");


}*/
