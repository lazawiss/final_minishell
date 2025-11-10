/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 02:01:17 by lzannis           #+#    #+#             */
/*   Updated: 2025/10/16 07:07:23 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	write (fd, s, ft_strlen(s));
}
/*
int	main(void)
{
	ft_putstr_fd("", 1);
	ft_putstr_fd("hello", 2);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("salut", 0);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("saaaaalut", 4);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("saaaaalut", 1);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("52468", 1);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("*_()!<>", 1);
}*/