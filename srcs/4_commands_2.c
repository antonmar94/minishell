/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_commands_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 19:25:56 by albzamor          #+#    #+#             */
/*   Updated: 2022/05/07 18:21:53 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



int export(t_shell *shell)
{
	t_env_list *new_list_var;
	char *var_name;
	char *var_content;
	if(!*shell->command_args)
		{
			env(shell);
			return(0);
		}
	if (!check_char(*shell->command_args, '='))
		return(0);
	var_name = cut_env_var_name(*(shell->command_args));
	var_content = cut_env_var_content(*(shell->command_args));
	print_var_content_text(var_name, var_content, shell);//TODO:borrar?
	if (change_var_content(shell, var_name, var_content))
		return (0);
	new_list_var = env_var_list_new(*(shell->command_args));
	env_var_add_back(&shell->env_list, new_list_var);
	return(0);
}

int unset(t_shell *shell)
{
	char *var_name;

	var_name = cut_env_var_name(*(shell->command_args));
	print_var_unset(var_name, shell);
	del_var_node_coincident(shell, var_name);
	return(0);
}


int env(t_shell *shell)
{
	print_env_list(shell->env_list);
	return(0);
}
