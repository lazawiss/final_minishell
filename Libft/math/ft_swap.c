/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:14:45 by lzannis           #+#    #+#             */
/*   Updated: 2025/07/11 15:53:32 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_swap(int *x, int *y)
{
	int	temp;

	temp = *x;
	*x = *y;
	*y = temp;
}

// int main(void)
// {
	// int a = 1;
	// int b = 2;
	// int *c = &a;
	// int *d = &b;
// 
	// printf("c = %d d = %d\n", *c, *d);
	// ft_swap(c, d);
	// printf("c = %d d = %d\n", *c, *d);
// 
// 
// }