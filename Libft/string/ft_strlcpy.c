/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 01:41:51 by lzannis           #+#    #+#             */
/*   Updated: 2025/06/18 01:41:55 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bsd/string.h>
#include "../libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t siz)
{
	size_t	i;
	size_t	src_len;

	i = 0;
	src_len = 0;
	while (src[src_len])
		src_len++;
	if (siz == 0)
		return (src_len);
	while (src[i] && i < (siz -1))
	{
		dst[i] = src[i];
		i++;
	}
	if (siz > 0)
		dst[i] = '\0';
	return (src_len);
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
    char source[15] = "";
	char destination[15] = "";


    memdisplay(source, 15);
	printf("Ma fonction, chaine de depart dst:");
    memdisplay(destination, 15);

    ft_strlcpy(destination, source,0);
	printf("%zu\n",ft_strlcpy(destination, source,5));

    printf("Ma fonction, chaine d'arrivee dst:");
    memdisplay(destination, 15);

    char sourca[15] = "";
	char destinationa[15] = "";

    printf("Vraie fonction, chaine de depart src:");
    memdisplay(sourca, 15);
	printf("Vraie fonction, chaine de depart dst:");
    memdisplay(destinationa, 15);

    strlcpy(destination,sourca,0);
	printf("%zu\n",strlcpy(destinationa,sourca,5));

	printf("Vraie fonction, chaine d'arrivee dst:");
    memdisplay(destinationa, 15);
    return (0);
}*/