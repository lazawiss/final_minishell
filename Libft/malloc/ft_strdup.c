/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 01:21:49 by lzannis           #+#    #+#             */
/*   Updated: 2025/10/16 05:27:49 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	size_t	i;
	char	*p;

	if (!s)
		return (NULL);
	len = 0;
	i = 0;
	while (s[len])
		len++;
	p = (char *)malloc(len + 1);
	if (!p)
		return (NULL);
	while (i < len)
	{
		p[i] = s[i];
		i++;
	}
	p[len] = '\0';
	return (p);
}

/*char	*ft_strdup(const char *s)
{
	char	*ptr;
	int		i;
	int		src_len;

	i = 0;
	src_len = 0;
	if (!*s)
		return (NULL);
	while (s[src_len])
		src_len++;
	ptr = malloc(1 * (src_len + 1));
	if (ptr == NULL)
		return (NULL);
	while (s[i])
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}*/
/*
void	memdisplay(char *data, int size)
{
    int loop;

    loop = 0;
    printf("\n");
    while (loop != size)
    {
        printf("[%d] ", (int)data[loop]);
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

int main(void)
{
	char *a;

	a = ft_strdup("poulet");
	memdisplay(a,23);

	char *b;

    b = strdup("poulet");
    memdisplay(b,23);

    return (0);
}*/
