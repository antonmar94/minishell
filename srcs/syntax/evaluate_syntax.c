/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 16:35:29 by albzamor          #+#    #+#             */
/*   Updated: 2022/10/04 18:59:26 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_empty(t_shell *shell)
{
	char	*aux_line;

	aux_line = shell->line;
	while (*aux_line && *aux_line == ' ')
		aux_line++;
	if (!*aux_line)
		return (1);
	return (0);
}

int	check_list_flag(char *list_arg)
{
	char	*flag;

	if (!list_arg)
		return (0);
	flag = list_arg;
	if (!ft_strncmp(flag, "-n", 2))
	{
		flag++;
		while (*flag && *flag == 'n')
			flag++;
		while (!*flag || *flag == ' ')
		{
			if (!ft_strncmp(flag, "-n", 2))
				return (0);
			else if (*flag != ' ')
				return (1);
			flag++;
		}
	}
	return (0);
}

int	check_arg_flag(t_shell *shell, char *argument, int no_add_flag)
{
	if (check_list_flag(argument) && no_add_flag == 1)
	{
		new_free(&argument);
		shell->size_com_args--;
		if (!(*shell->line_walker))
			return (-1);
		return (1);
	}
	return (0);
}

int	check_syntax(t_shell *shell)
{
	if (check_empty(shell))
		return (1);
	if (check_quotes_syntax(shell->line))
	{
		syntax_error(shell);
		return (1);
	}
	if (check_arrow_syntax(shell->line, '>')
		|| check_arrow_syntax(shell->line, '<'))
	{
		syntax_error(shell);
		return (1);
	}
	if (check_pipe_syntax(shell))
	{
		syntax_error(shell);
		return (1);
	}
	return (0);
}
