/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 17:35:27 by lzannis           #+#    #+#             */
/*   Updated: 2025/05/30 13:54:08 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	tmp = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
}

/*
int	main(void)
{
	t_list *lst = NULL;

	t_list *new = ft_lstnew(&new);

	ft_lstadd_back(&lst, new);

	new = ft_lstnew(&new);

	ft_lstadd_back(&lst, new);

	printf("dernier element %p\n",lst);
}*/
