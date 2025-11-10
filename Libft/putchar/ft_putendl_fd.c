/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 02:03:39 by lzannis           #+#    #+#             */
/*   Updated: 2025/06/18 02:03:48 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}
/*
int	main(void)
{
	ft_putendl_fd("grrrrr1", 1);
	ft_putendl_fd("grrrrr2", 2);
	ft_putendl_fd("grrrrr0", 0);
	ft_putendl_fd("grrrrr3", 3);
	ft_putendl_fd("grrrrr4", 4);
	ft_putendl_fd("grrrrr5", 5);
	ft_putendl_fd("grrrrr-1", -1);
	return (0);

}*/