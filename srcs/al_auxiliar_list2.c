/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   al_auxiliar_list2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 19:30:12 by albzamor          #+#    #+#             */
/*   Updated: 2022/06/18 16:42:20 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_var_content(t_env_list	*del_copy)
{
	free(del_copy->var_name);
	free(del_copy->var_content);
	free(del_copy);
}

/* modify variable content if it already exists otherwise returns 1*/
int	del_var_node_coincident(t_shell *shell, char *var_name_to_find)
{
	t_env_list	*copy;
	t_env_list	*del_copy;

	copy = shell->env_list_plus;
	while (copy->next)
	{
		if (!ft_strcmp(copy->next->var_name, var_name_to_find))
		{
			del_copy = copy->next;
			copy->next = copy->next->next;
			free_var_content(del_copy);
			return (1);
		}
		copy = copy->next;
	}
	if (!ft_strcmp(copy->next->var_name, var_name_to_find))
	{
		del_copy = copy->next;
		copy->next = copy->next->next;
		free_var_content(del_copy);
		return (1);
	}
	return (0);
}
