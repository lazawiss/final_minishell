/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 01:14:15 by lzannis           #+#    #+#             */
/*   Updated: 2025/06/18 01:19:37 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned int	i;
	unsigned char	*cast_s;

	i = 0;
	cast_s = (unsigned char *)s;
	while (i < n)
	{
		cast_s[i] = '\0';
		i++;
	}
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
        printf("[%d] ", data[loop]);
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
    char source[15] = "Hello";

    printf("Ma fonction, chaine de depart :");
    memdisplay(source, 15);
    ft_bzero(source,(7));

    printf("Ma fonction, chaine d'arrivee:");
    memdisplay(source, 15);

    char sourca[15] = "Hello";

    printf("Vraie fonction, chaine de depart :");
    memdisplay(sourca, 15);

    bzero(sourca,(7));

	printf("Vraie fonction, chaine d'arrivee :");
    memdisplay(sourca, 15);
    return (0);
}*/