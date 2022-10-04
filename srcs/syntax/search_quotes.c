/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 19:13:39 by antonmar          #+#    #+#             */
/*   Updated: 2022/10/04 18:58:47 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_line_command(t_shell *shell)
{
	t_arglist	*aux_free;

	if (shell->arg_list)
	{
		aux_free = shell->arg_list;
		shell->command = shell->arg_list->content;
		shell->arg_list = shell->arg_list->next;
		free(aux_free);
		aux_free = NULL;
		if (shell->arg_list && check_list_flag(shell->arg_list->content))
		{
			shell->command_flag = "-n";
			aux_free = shell->arg_list;
			shell->free_aux_list = shell->arg_list->content;
			shell->arg_list = shell->arg_list->next;
			free(aux_free);
		}
	}
}

int	get_add_flag(int no_add_flag, t_shell *shell)
{
	if (shell->size_com_args > 1 && !check_list_flag(last_arg(shell->arg_list)))
		no_add_flag = -1;
	if (no_add_flag >= 0 && check_list_flag(last_arg(shell->arg_list)))
		no_add_flag = 1;
	else if (no_add_flag == 1)
		no_add_flag = -1;
	return (no_add_flag);
}

int	add_arg_tolist(t_shell *shell, int no_add_flag)
{
	char	*argument;
	int		size_arg;
	int		check_arg;

	size_arg = size_argument(shell);
	argument = ft_substr(shell->line_walker, 0, size_arg);
	while (*shell->line_walker && (*shell->line_walker == ' ' || size_arg > 0))
	{
		shell->line_walker++;
		size_arg--;
	}
	if (argument)
	{
		argument = find_dollar_quotes(argument);
		argument = arg_creator(shell, &argument);
		check_arg = check_arg_flag(shell, argument, no_add_flag);
		if (check_arg < 0)
			return (0);
		else if (check_arg)
			return (1);
		arglstadd_back(&shell->arg_list, arg_node_new(argument));
	}
	if (!(*shell->line_walker))
		return (0);
	return (1);
}

void	create_array_args(t_shell *shell)
{
	t_arglist	*holder_first;
	char		**begin_matrix;

	holder_first = shell->arg_list;
	if (!holder_first)
		return ;
	shell->command_plus_args = (char **)malloc(sizeof(char *)
			* (shell->size_com_args + 1));
	ft_memset(shell->command_plus_args, 0, sizeof(char **));
	begin_matrix = shell->command_plus_args;
	while (holder_first && holder_first->content && shell->size_com_args > 0)
	{
		*shell->command_plus_args = ft_strdup(holder_first->content);
		holder_first = holder_first->next;
		shell->command_plus_args++;
	}
	*shell->command_plus_args = NULL;
	shell->command_plus_args = begin_matrix;
}

int	split_arguments(t_shell *shell)
{
	char		**to_free;
	int			no_add_flag;

	no_add_flag = 0;
	shell->size_com_args = 0;
	shell->line_walker = shell->line;
	while (*shell->line_walker && *shell->line_walker == ' ')
		shell->line_walker++;
	if (*shell->line_walker)
		shell->size_com_args = 1;
	while (add_arg_tolist(shell, no_add_flag))
	{
		no_add_flag = get_add_flag(no_add_flag, shell);
		shell->size_com_args++;
	}
	to_free = shell->command_plus_args;
	create_array_args(shell);
	free_matrix(to_free);
	shell->command_args = shell->command_plus_args;
	if (shell->command_args)
		shell->command_args++;
	if (shell->arg_list)
		add_line_command(shell);
	return (0);
}
