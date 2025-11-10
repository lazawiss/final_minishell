/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 22:08:16 by lzannis           #+#    #+#             */
/*   Updated: 2025/05/30 13:54:38 by lzannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*listi;
	void	*tmp;

	listi = NULL;
	while (lst)
	{
		tmp = f(lst->content);
		ft_lstadd_back(&listi, ft_lstnew(tmp));
		if (!listi)
		{
			ft_lstclear(&listi, del);
			return (NULL);
		}
		lst = lst->next;
	}
	return (listi);
}
/*
void *donothing(void *i)
{
	(void)i;
	return (NULL);
}

int	main(void)
{
	t_list *lst = NULL;
	t_list *result = ft_lstmap(lst, donothing, NULL);
	if (result == NULL)
		printf("yes");

}*/
