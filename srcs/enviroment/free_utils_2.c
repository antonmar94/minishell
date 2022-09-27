/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 19:05:22 by albzamor          #+#    #+#             */
/*   Updated: 2022/09/27 01:12:02 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

char	**create_env_matrix(t_shell *shell)
{
	t_env_list	*holder_first;
	char		*aux_envp;
	char		**minishell_envp;
	int			i;

	i = 0;
	aux_envp = NULL;
	holder_first = shell->env_list;
	minishell_envp = malloc (sizeof(char *)
			* (ft_lst_env_size(shell->env_list) + 1));
	while (holder_first)
	{
		aux_envp = ft_strjoin(holder_first->var_name, "=");
		minishell_envp[i] = ft_strjoin(aux_envp, holder_first->var_content);
		new_free(&aux_envp);
		holder_first = holder_first->next;
		i++;
	}
	minishell_envp[i] = NULL;
	return (minishell_envp);
}
