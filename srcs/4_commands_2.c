/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_commands_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 19:25:56 by albzamor          #+#    #+#             */
/*   Updated: 2022/02/03 19:04:47 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* boolean to find a variable */
int look_for_var_name(t_shell *shell, char *var_name_to_find)
{
	t_env_list *copy;

	copy = shell->env_list;
	while (copy->next)
	{
		if (!ft_strcmp(shell->env_list->var_name,var_name_to_find))
			return(1);
		copy = copy->next;
	}
	if (!ft_strcmp(shell->env_list->var_name,var_name_to_find))
		return(1);
	return(0);
}

/* modify variable content if it already exists otherwise returns 1*/
int change_var_content(t_shell *shell, char *var_name_to_find,
	char *var_content_to_change)
{
	t_env_list *copy;

	copy = shell->env_list;
	while (shell->env_list->next)
	{
		if (!ft_strcmp(shell->env_list->var_name,var_name_to_find))
		{
			shell->env_list->var_content = var_content_to_change;
			shell->env_list = copy;
			return(1);
		}
		shell->env_list = shell->env_list->next;
	}
	if (!ft_strcmp(shell->env_list->var_name,var_name_to_find))
	{
		shell->env_list->var_content = var_content_to_change;
		shell->env_list = copy;
		return(1);
	}
	shell->env_list = copy;
	return(0);
}







int export(t_shell *shell)
{
	t_env_list *new_list_var;
	char *var_name;
	char *var_content;

	var_name = cut_env_var_name(*(shell->command_args));
	var_content = cut_env_var_content(*(shell->command_args));



	if (change_var_content(shell, var_name, var_content))
		return (0);
	/* if (**(shell->command_args) != '=') comprobar errores en cut
	{
		shell->command_args++;
	} */

	printf(RED"\n\n AÑADIENDO NUEVA VARIABLE\n"RESET);
	new_list_var = env_var_list_new(*(shell->command_args));
	env_var_add_back(&shell->env_list, new_list_var);
	//print_env_list(shell->env_list);

	return(0);
}

int env(t_shell *shell)
{
	print_env_list(shell->env_list);
	return(0);
}
