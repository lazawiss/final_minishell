/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 01:28:07 by lzannis           #+#    #+#             */
/*   Updated: 2025/05/30 13:54:46 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
/*
int	main(void)
{
	t_list *lst = NULL;
	printf("taille de lst %d\n",ft_lstsize(lst));

	t_list *new = ft_lstnew(&new);

	ft_lstadd_front(&lst, new);
	printf("taille de lst %d\n",ft_lstsize(lst));

	new = ft_lstnew(&new);

	ft_lstadd_front(&lst, new);

	printf("taile de lst %d\n",ft_lstsize(lst));
}*/
