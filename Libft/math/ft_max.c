/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:56:45 by lzannis           #+#    #+#             */
/*   Updated: 2025/07/11 15:51:42 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	max(int *tab, unsigned int len)
{
	unsigned int	i;
	int				max;

	if (*tab == 0)
		return (0);
	i = 0;
	max = -2147483648;
	while (tab[i] && i < len)
	{
		if (tab[i] > max)
		{
			max = tab[i];
		}
		i++;
	}
	return (max);
}
// int	main(void)
// {
// 	int	tab[5] = {45, 5, 87, 639,4};
// 	int tabi[0];

// 	printf("%d\n", max(tab, 5));
// 	printf("%d\n", max(tabi, 5));

// }