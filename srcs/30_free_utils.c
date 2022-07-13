/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   30_free_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 11:02:23 by albzamor          #+#    #+#             */
/*   Updated: 2022/07/13 17:13:49 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	new_free(char **ptr)
{
	free (*ptr);
	*ptr = NULL;
}

void	free_all_struct(t_shell *shell)
{
	if (shell->line)
		new_free(&shell->line);
	shell->line = NULL;
	shell->has_pipes = 0;
	new_free(&shell->env_list_plus->next->var_content);
	free_parent(shell);
}

void	free_parent(t_shell *shell)
{
	free_arg_list(&shell->arg_list);
	shell->size_com_args = 0;
	if (shell->command)
		new_free(&shell->command);
	if (shell->command_flag)
	{
		new_free(&shell->free_aux_list);
		shell->command_flag = NULL;
	}
}

void	free_arg_list(t_arglist **arg_lst)
{
	t_arglist	*cleaner;
	t_arglist	*aux;

	cleaner = *arg_lst;
	while (cleaner)
	{
		aux = cleaner->next;
		free(cleaner->content);
		free(cleaner);
		cleaner = aux;
	}
	*arg_lst = NULL;
}
