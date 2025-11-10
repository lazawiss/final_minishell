/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_absolute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:08:34 by lzannis           #+#    #+#             */
/*   Updated: 2025/07/11 15:36:04 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_absolute(int x, int y)
{
	int	abs1;
	int	abs2;

	if (x < 0)
		x = -x;
	if (y < 0)
		y = -y;
	abs1 = 1;
	abs2 = 1;
	abs1 *= x;
	abs2 *= y;
	if (abs1 > abs2)
		return (x);
	else
		return (y);
}

/* int	main(void)
{
	int a = -5;
	int b = -12;

	printf("%d\n", ft_absolute(a, b));

} */
