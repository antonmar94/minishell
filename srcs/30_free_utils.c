/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   30_free_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 11:02:23 by albzamor          #+#    #+#             */
/*   Updated: 2022/06/18 15:44:16 by albzamor         ###   ########.fr       */
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
	free_parent(shell);
}

void	free_parent(t_shell *shell)
{
	free_arg_list(&shell->arg_list);
	shell->size_com_args = 0;
	shell->command = NULL;
	shell->command_flag = NULL;
}

void	free_arg_list(t_arglist **arg_lst)
{
	t_arglist	*cleaner;
	t_arglist	*aux;

	cleaner = *arg_lst;
	while (cleaner)
	{
		aux = cleaner->next;
		free(cleaner);
		cleaner = aux;
	}
	*arg_lst = NULL;
}
