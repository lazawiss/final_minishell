/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 21:49:47 by lzannis           #+#    #+#             */
/*   Updated: 2025/05/30 13:54:31 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
/*
void	a(void *s)
{	
	printf("HELLOOOOOOOOOO %d\n", *(int *)(s));
}

int main(void)
{
	int	x = 42;
	int	y = 43;

	t_list *lst = NULL;
	printf("taille de lst %d\n",ft_lstsize(lst));

	t_list *new = ft_lstnew(&x);

	ft_lstadd_front(&lst, new);
	printf("taille de lst %d\n",ft_lstsize(lst));

	new = ft_lstnew(&y);

	ft_lstadd_front(&lst, new);

	printf("taile de lst %d\n",ft_lstsize(lst));

	ft_lstiter(lst, &a);

}*/
