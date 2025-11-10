/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 01:15:08 by lzannis           #+#    #+#             */
/*   Updated: 2025/06/18 01:19:41 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*ptr;
	size_t	i;

	i = 0;
	i--;
	if (size != 0 && (i / size) < nmemb)
		return (NULL);
	if (nmemb == 0)
		return (malloc(0));
	if (size == 0)
		return (malloc(0));
	ptr = malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}

/*
void    memdisplay(char *data, int size)
{
    int loop;

    loop = 0;
    printf("\n");
    while (loop != size)
    {
        printf("[%d],", (int)data[loop]);
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
}

int	main(void)
{
	char *c = ft_calloc(1,8);
	if (c[0] == 0)
		printf("OK\n");
	memdisplay(c, 23);

    char *d = calloc(1,8);
	if (d[0] == 0)
		printf("OK\n");
    memdisplay(d, 23);

	return (0);
}*/