/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 01:44:38 by lzannis           #+#    #+#             */
/*   Updated: 2025/05/30 13:54:34 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}
/*
int	main(void)
{
	t_list *lst = NULL;

	t_list *new = ft_lstnew(&new);

	ft_lstadd_front(&lst, new);

	new = ft_lstnew(&new);

	ft_lstadd_front(&lst, new);

	printf("dernier element %p\n",ft_lstlast(lst));
}*/
