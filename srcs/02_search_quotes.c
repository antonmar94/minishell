/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_search_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 19:13:39 by antonmar          #+#    #+#             */
/*   Updated: 2022/05/08 14:43:31 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_line_command(t_shell *shell)
{
	t_arglist	*aux_free;

	if (shell->arg_list)
	{
		shell->command = shell->arg_list->content;
		aux_free = shell->arg_list;
		shell->arg_list = shell->arg_list->next;
		free(aux_free);
		aux_free = NULL;
		if (shell->arg_list && check_list_flag(shell->arg_list->content))
		{
			shell->command_flag = "-n";
			aux_free = shell->arg_list;
			shell->arg_list = shell->arg_list->next;
		}
	}
}

int	add_arg_tolist(t_shell *shell)
{
	char		*argument;
	int			size_arg;

	size_arg = size_argument(shell);
	argument = ft_substr(shell->line_walker, 0, size_argument(shell));
	while (*shell->line_walker && (*shell->line_walker == ' ' || size_arg > 0))
	{
		shell->line_walker++;
		size_arg--;
	}
	if (argument)
	{
		argument = arg_creator(shell, &argument);
		arglstadd_back(&shell->arg_list, arg_node_new(argument));
	}
	if (!(*shell->line_walker))
		return (0);
	return (1);
}

void	create_array_args(t_shell *shell)
{
	t_arglist	*holder_first;
	int			i;

	i = 0;
	holder_first = shell->arg_list;
	shell->command_plus_args = malloc(sizeof(char *) * shell->size_com_args + 1);
	while (holder_first && shell->size_com_args > 0)
	{
		shell->command_plus_args[i] = holder_first->content;
		holder_first = holder_first->next;
		i++;
	}
	shell->command_plus_args[i] = NULL;
}

/*
	Create argument list and command_plus_args array
*/
int	split_arguments(t_shell *shell)
{
	int			i;

	i = 1;
	shell->size_com_args = 0;
		shell->line_walker = shell->line;
	while (*shell->line_walker && *shell->line_walker == ' ')
		shell->line_walker++;
	if (*shell->line_walker)
		shell->size_com_args = 1;
	while (add_arg_tolist(shell))
		shell->size_com_args++;
  	create_array_args(shell);
	shell->command_args = shell->command_plus_args;
	if (shell->command_args)
		shell->command_args++;
	if (shell->arg_list)
		add_line_command(shell);
	return (0);
}
