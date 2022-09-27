/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 00:44:19 by albzamor          #+#    #+#             */
/*   Updated: 2022/09/27 02:12:41 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env_list	*order_env_list(t_env_list *env_list)
{
	t_env_list	*copy;
	t_env_list	*copy2;
	char		*aux;

	copy = env_list;
	while (copy->next)
	{
		copy2 = copy->next;
		while (copy2)
		{
			if (ft_strcmp(copy->var_name, copy2->var_name) > 0)
			{
				aux = copy->var_name;
				copy->var_name = copy2->var_name;
				copy2->var_name = aux;
				aux = copy->var_content;
				copy->var_content = copy2->var_content;
				copy2->var_content = aux;
			}
			copy2 = copy2->next;
		}
		copy = copy->next;
	}
	return (env_list);
}
