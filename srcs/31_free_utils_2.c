/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   31_free_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 19:05:22 by albzamor          #+#    #+#             */
/*   Updated: 2022/06/19 19:44:10 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_isdigit_str(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

t_env_list	*free_name_contend(t_env_list	*copy)
{
	t_env_list	*copy2;

	if (copy->var_name)
	{
		free(copy->var_name);
		copy->var_name = NULL;
	}
	if (copy->var_content)
	{
		free(copy->var_content);
		copy->var_content = NULL;
	}
	copy2 = copy->next;
	free(copy);
	copy = copy2;
	return (copy);
}

void	free_env_list(t_env_list *envp)
{
	t_env_list	*copy;

	copy = envp;
	while (copy->next)
		copy = free_name_contend(copy);
	if (copy->var_name)
	{
		free(copy->var_name);
		copy->var_name = NULL;
	}
	if (copy->var_content)
	{
		free(copy->var_content);
		copy->var_content = NULL;
	}
	free(copy);
}
