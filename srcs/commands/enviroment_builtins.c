/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment_builtins.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 19:25:56 by albzamor          #+#    #+#             */
/*   Updated: 2022/10/04 19:41:48 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	unset(t_shell *shell)
{
	while (*shell->command_args)
	{
		if (!*shell->command_args || ft_strcmp(*shell->command_args, "0") == 0
			|| ft_strcmp(*shell->command_args, "?") == 0)
		{
			identifier_enviro_error(shell);
			return (0);
		}
		del_var_node_coincident(shell, *shell->command_args);
		new_free(&*shell->command_args);
		shell->command_args++;
	}
	return (0);
}

int	unset_util(char *var_to_unset, t_shell *shell)
{
	//REVISAR
	del_var_node_coincident(shell, var_to_unset);
	new_free(&var_to_unset);
	return (0);
}

int	env(t_shell *shell)
{
	if (*shell->command_args)
	{
		error_too_many_args(shell);
		return (0);
	}
	print_env_list(shell->env_list);
	return (0);
}

void	exit_minishell(t_shell *shell)
{
	if (shell->size_com_args == 1)
	{
		shell->exit_return = 0;
		print_header(shell, "thanks for using");
		shell->exit = 1;
	}
	if (shell->arg_list && *shell->arg_list->content)
	{
		if (shell->arg_list && shell->arg_list->next)
		{
			error_too_many_args(shell);
			return ;
		}
		if (!ft_isdigit_str(shell->arg_list->content))
		{
			error_not_numeric(shell);
			shell->exit_return = 255;
			shell->exit = 1;
		}
		else
			exit_return(shell);
	}
}

void	exit_return(t_shell *shell)
{
	int	number;

	number = ft_atoi(shell->arg_list->content);
	while (number < 0)
		number += 256;
	if (number >= 0 && number <= 255)
	{
		shell->exit_return = number;
		print_header(shell, "thanks for using ");
		shell->exit = 1;
	}
	if (number > 255)
	{
		number = number % 256;
		shell->exit_return = number;
		print_header(shell, "thanks for using ");
		shell->exit = 1;
	}
}
