/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04b_evaluate_syntax_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 16:35:29 by albzamor          #+#    #+#             */
/*   Updated: 2022/06/18 16:50:39 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_syntax(t_shell *shell)
{
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
