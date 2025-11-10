/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:43:32 by lzannis           #+#    #+#             */
/*   Updated: 2025/07/11 15:20:24 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	check_base(int n, unsigned int base)
{
	unsigned int	i;
	const char		*lower = "0123456789abcdef";
	const char		*upper = "0123456789ABCDEF";

	i = 0;
	if (base > 16 || base < 2)
		return (0);
	while (i < base)
	{
		if (n == lower[i] || n == upper[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_atoi_base(const char *nbr, unsigned int base)
{
	int	i;
	int	sign;
	int	n;

	i = 0;
	sign = 1;
	n = 0;
	if (nbr[i] == '+' || nbr[i] == '-')
	{
		if (nbr[i] == '-')
			sign = -1;
		i++;
	}
	while (nbr[i] && check_base(nbr[i], base))
	{
		n *= base;
		if (nbr[i] >= '0' && nbr[i] <= '9')
			n += nbr[i] - '0';
		else if (nbr[i] >= 'a' && nbr[i] <= 'f')
			n += (nbr[i] - 'a') + 10;
		else if (nbr[i] >= 'A' && nbr[i] <= 'F')
			n += (nbr[i] - 'A') + 10;
		i++;
	}
	return (n * sign);
}

// int	main(void)
// {

// 	printf("%d\n", ft_atoi_base("01pp",2));
// }