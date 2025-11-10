/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 01:57:24 by lzannis           #+#    #+#             */
/*   Updated: 2025/06/18 01:57:30 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned int	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = c;
		i++;
	}
	return (s);
}
/*
#include <stdio.h>

void    memdisplay(char * data, int size)
{
    int loop;

    loop = 0;
    printf("\n");
    while (loop != size)
    {
        printf("[%d]", data[loop]);
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

int main(void)
{
    char source[15] = "";
    int c = '1';

    printf("source :");
    memdisplay(source, 15);

    ft_memset(source,c,5);

    printf("Source :");
    memdisplay(source, 15);

    char sourca[15] = "";
    int d = '1';

    printf("source :");
    memdisplay(sourca, 15);

    memset(sourca,d,5);

	printf("Source :");
    memdisplay(sourca, 15);
    return (0);
}*/