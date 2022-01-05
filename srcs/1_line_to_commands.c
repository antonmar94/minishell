/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_list_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 13:25:26 by albzamor          #+#    #+#             */
/*   Updated: 2022/01/03 13:37:29 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* split the read line into command (first) and args (rest) */
void	split_line_to_command(t_shell *shell)
{


	shell->size_line = ft_wordcount(shell->line, ' ');
	shell->command_plus_args = ft_split(shell->line, ' ');
	shell->command = shell->command_plus_args[0];
	if(shell->command_plus_args[1] && (shell->command_plus_args[1][0] == '-'))
		separate_args(shell);
	else
		separate_args_no_flag(shell);

}


void separate_args(t_shell *shell)
{

	int i;

	i = 0;
	shell->command_flag = ft_strdup(shell->command_plus_args[1]);
	if (shell->size_line > 2)
	{
		shell->command_args = malloc(sizeof(char*) * shell->size_line - 2);
		while( i + 2 < shell->size_line )
		{
			shell->command_args[i]=ft_strdup(shell->command_plus_args[i+2]);
			i ++;
		}
	}
	else
		shell->command_args = NULL;
}

void separate_args_no_flag(t_shell *shell)
{
	int i;

	i = 0;
	if (shell->size_line > 1)
	{
		shell->command_args = malloc(sizeof(char*) * shell->size_line - 1);
		while( i + 1 < shell->size_line )
		{
			shell->command_args[i]=ft_strdup(shell->command_plus_args[i+1]);
			i ++;
		}
	}
	else
		shell->command_args = NULL;
}