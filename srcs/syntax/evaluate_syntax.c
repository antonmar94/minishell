/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_syntax_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 16:35:29 by albzamor          #+#    #+#             */
/*   Updated: 2022/09/24 14:53:59 by albzamor         ###   ########.fr       */
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
