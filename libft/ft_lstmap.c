/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 13:09:54 by albzamor          #+#    #+#             */
/*   Updated: 2021/06/11 12:58:25 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))

{
	t_list	*first;
	t_list	*listf;

	if (lst != NULL && f != NULL)
	{
		first = ft_lstnew(f(lst->content));
		listf = first;
		while (lst->next)
		{
			lst = lst->next;
			listf->next = ft_lstnew((f(lst->content)));
			if (listf->next == NULL)
			{
				ft_lstclear(&first, del);
				return (NULL);
			}
			listf = listf->next;
		}
		return (first);
	}
	return (NULL);
}
