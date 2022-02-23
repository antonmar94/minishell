/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 22:42:47 by albzamor          #+#    #+#             */
/*   Updated: 2022/02/23 14:18:00 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*copy;

	while (*lst != NULL)
	{
		copy = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = copy;
	}
}
