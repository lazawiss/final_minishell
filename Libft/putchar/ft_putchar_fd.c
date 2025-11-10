/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 02:02:06 by lzannis           #+#    #+#             */
/*   Updated: 2025/06/18 02:03:57 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write (fd, &c, 1);
}
/*
int	main(void)
{
	ft_putchar_fd('d', 1);
	ft_putchar_fd('\n', 2);
	ft_putchar_fd(' ', 2);
	ft_putchar_fd('2', 1);
	ft_putchar_fd('0', 1);
	ft_putchar_fd('*', -1);
	ft_putchar_fd('\n', 3);
	ft_putchar_fd('4', 42);
	ft_putchar_fd('4', 2);
	return (0);
}*/