/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliar_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 15:52:46 by albzamor          #+#    #+#             */
/*   Updated: 2022/09/24 14:55:32 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*cut_env_var_name(char *str_whith_equal_in)
{
	char	*var_name;
	char	*env_var_walking;
	int		i;

	env_var_walking = str_whith_equal_in;
	i = 0;
	while (*env_var_walking && *env_var_walking != '=')
	{
		i++;
		env_var_walking++;
	}
	var_name = ft_substr(str_whith_equal_in, 0, i);
	return (var_name);
}

char	*cut_env_var_content(char *str_whith_equal_in)
{
	char	*var_content;
	char	*env_var_walking;
	int		start;

	env_var_walking = str_whith_equal_in;
	start = 0;
	while (*env_var_walking != '=')
	{
		start++;
		env_var_walking++;
	}
	start++;
	env_var_walking++;
	var_content = ft_strdup(env_var_walking);
	return (var_content);
}

/* modify variable content if it already exists otherwise returns 1*/
int	change_var_content(t_shell *shell, char *var_name_to_find,
	char *var_content_to_change)
{
	t_env_list	*copy;

	copy = shell->env_list_plus;
	while (copy->next)
	{
		if (!ft_strcmp(copy->var_name, var_name_to_find))
		{
			new_free(&copy->var_content);
			copy->var_content = var_content_to_change;
			return (1);
		}
		copy = copy->next;
	}
	if (!ft_strcmp(copy->var_name, var_name_to_find))
	{
		new_free(&copy->var_content);
		copy->var_content = var_content_to_change;
		return (1);
	}
	return (0);
}

int	varname_found(char **var_name, char	**var_content, t_shell *shell)
{
	if (!**var_name || ft_strcmp(*var_name, "0") == 0
		|| ft_strcmp(*var_name, "?") == 0)
	{
		identifier_enviro_error(shell);
		return (1);
	}
	if (change_var_content(shell, *var_name, *var_content))
	{
		new_free(&*var_name);
		return (1);
	}
	return (0);
}
