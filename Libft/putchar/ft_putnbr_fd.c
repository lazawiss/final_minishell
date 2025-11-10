/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 02:00:04 by lzannis           #+#    #+#             */
/*   Updated: 2025/06/18 02:05:20 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n > 9)
		ft_putnbr_fd((n / 10), fd);
	ft_putchar_fd(((n % 10) + '0'), fd);
}
/*
int	main(void)
{
	ft_putnbr_fd(0, 0);
	ft_putchar_fd('\n', 1);
	ft_putnbr_fd(0, 1);
	ft_putchar_fd('\n', 1);
	ft_putnbr_fd(0, 2);
	ft_putchar_fd('\n', 1);
	ft_putnbr_fd(-42, 0);
	ft_putchar_fd('\n', 1);
	ft_putnbr_fd(-2147483648, 0);
	ft_putchar_fd('\n', 1);
	ft_putnbr_fd(7581, 2);
	ft_putchar_fd('\n', 1);
	ft_putnbr_fd(2147483647, 2);
	ft_putchar_fd('\n', 1);
	return (0);
}*/