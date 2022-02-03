/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_commands_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 19:25:56 by albzamor          #+#    #+#             */
/*   Updated: 2022/02/03 15:33:17 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int export(t_shell *shell)
{
	t_env_list *new_list_var;

	/* if (**(shell->command_args) != '=')
	{
		shell->command_args++;
	} */

	new_list_var = env_var_list_new(*(shell->command_args));
	env_var_add_back(&shell->env_list, new_list_var);
	printf("que pasa");
	print_env_list(shell->env_list);

	return(0);
}