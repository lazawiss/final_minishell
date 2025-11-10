/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 13:25:26 by lzannis           #+#    #+#             */
/*   Updated: 2025/07/11 15:14:01 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_strlen_atof(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static int	ft_strlen_post_point(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] && str[i] != '.')
		i++;
	j = i;
	while (str[j])
		j++;
	return (j - i -1);
}

static double	ft_power(t_atof *atof)
{
	double	power;

	power = 1.0 / 10;
	while (atof->len)
	{
		atof->nbr *= power;
		atof->len--;
	}
	return (atof->nbr);
}

static int	ft_atoi_atof(char *str)
{
	int		nb;
	int		i;

	i = 0;
	nb = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && str[i] != '.')
	{
		nb = (nb * 10) + (str[i] - '0');
		i++;
	}
	return (nb);
}

double	ft_atof(char *str)
{
	t_atof	atof;

	atof.nbr = 0;
	atof.sign = 1;
	atof.i = 0;
	atof.len = ft_strlen_post_point(str);
	if (str[atof.i] == '-')
		atof.sign = -1;
	atof.i = ft_strlen_atof(str) - atof.len;
	atof.nb = ft_atoi_atof(str);
	if (str[atof.i] == '.')
		atof.i++;
	while (str[atof.i])
	{
		atof.nbr = (atof.nbr * 10) + (str[atof.i] - '0');
		atof.i++;
	}
	atof.nbr = ft_power(&atof);
	return ((atof.nb + atof.nbr) * atof.sign);
}
