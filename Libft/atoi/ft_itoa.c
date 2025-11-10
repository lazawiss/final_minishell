/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 13:35:21 by lzannis           #+#    #+#             */
/*   Updated: 2025/05/30 13:51:02 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	n_size(int n)
{
	int			i;
	int long	nb;

	i = 0;
	nb = n;
	if (nb < 0)
	{
		i++;
		nb *= -1;
	}
	while (nb > 9)
	{
		nb /= 10;
		i++;
	}
	i++;
	return (i);
}

char	*ft_itoa(int n)
{
	char		*ptr;
	int			i;
	int long	nb;

	i = n_size(n);
	nb = n;
	ptr = (char *)malloc (sizeof(char) * (i + 1));
	if (!ptr)
		return (NULL);
	ptr[i] = '\0';
	if (nb < 0)
	{
		ptr[0] = '-';
		nb = -nb;
	}
	else if (nb == 0)
		ptr[0] = '0';
	while (nb > 0)
	{
		i--;
		ptr[i] = (nb % 10) + '0';
		nb = nb / 10;
	}
	return (ptr);
}
/*
void	memdisplay(char * data, int size)
{
	int	loop;

	loop = 0;
	printf("\n");
	while (loop != size)
	{
		printf("%c ", data[loop]);
		loop +=1;
	}
	loop = 0;
	printf("\n");
	while (loop != size)
	{
		printf("_ ");
		loop +=1;
	}
	printf("\n");
	printf("\n");
	printf("\n");
}

int	main(void)
{
	char *a = ft_itoa(-623);
	char *b = ft_itoa(-2147483648);
	char *c = ft_itoa(-156);
	char *d = ft_itoa(-0);
	char *e = ft_itoa(2147483647);
	char *f = ft_itoa(1629905861);
	char *g = ft_itoa(-1234);
	char *h = ft_itoa(-5859);


	printf("a:");
	memdisplay(a, 15);

	printf("b :");
	memdisplay(b, 15);

	printf("c :");
	memdisplay(c, 15);

	printf("d :");
	memdisplay(d, 15);

	printf("e :");
	memdisplay(e, 15);

	printf("f :");
	memdisplay(f, 15);

	printf("g :");
	memdisplay(g, 15);

	printf("h :");
	memdisplay(h, 15);

	return (0);
}

int	main(void)
{
	printf("%s\n", ft_itoa(-623));
	printf("%s\n", ft_itoa(156));
	printf("%s\n", ft_itoa(-0));
	printf("%s\n", ft_itoa(2147483647));
	printf("%s\n", ft_itoa(-2147483648));

}*/
