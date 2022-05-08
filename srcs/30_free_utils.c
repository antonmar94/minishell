/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   30_free_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 11:02:23 by albzamor          #+#    #+#             */
/*   Updated: 2022/05/08 12:27:09 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_shell(t_shell *shell)
{
	if(shell->aux_pointer->final_str)
		new_free(&shell->aux_pointer->final_str);

	all_clear(&shell->arg_list);
	free_and_reset_values(shell);
}

void	del_list(t_shell	*shell)
{
	t_arglist *copy;
	copy = shell->arg_list;
	while (copy)
	{
		if(copy->content)
		{
			free(copy->content);
			copy->content = NULL;
		}
		copy = copy->next;	
	}
	shell->arg_list = copy;
}

void	free_env_list(t_env_list *envp)
{

	t_env_list *copy;
	t_env_list *copy2;
	copy = envp;
	while (copy->next)
	{
		if(copy->var_name)
		{
			free(copy->var_name);
			copy->var_name = NULL;
		}
		if(copy->var_content)
		{
			free(copy->var_content);
			copy->var_content = NULL;

		}
		copy2 = copy->next;
		free(copy);
		copy = copy2;
	}
	if(copy->var_name)
	{
		free(copy->var_name);
		copy->var_name = NULL;
	}
	if(copy->var_content)
	{
		free(copy->var_content);
		copy->var_content = NULL;
	}
	free(copy);
}

void	free_and_reset_values(t_shell *shell)
{
	if(shell->line)
	{
			if(shell->line)
				free(shell->line);
			shell->line = NULL;

	}
	shell->size_line = 0;
	shell->size_args = 0;
	shell->command = NULL;
}
