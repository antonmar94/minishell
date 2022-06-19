/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 11:50:06 by albzamor          #+#    #+#             */
/*   Updated: 2022/06/19 20:59:11 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_error(t_shell *shell, char *elem_err, int error_code)
{
	shell->exit_return = error_code;
	perror(ft_strjoin(RED"minishell: ", elem_err));
	errno = 0;
	return (1);
}

void	command_error(t_shell *shell, char *command)
{
	if (command)
	{
		shell->exit_return = 127;
		write(2, RED "minishell: ", 18);
		write(2, command, ft_strlen(command));
		ft_putstr_fdnl(": command not found" RESET, 2);
	}
}

int	identifier_enviro_error(t_shell *shell)
{
	shell->exit_return = 153;
	write(2, RED "minishell: ", 18);
	ft_putstr_fdnl("not a valid identifier" RESET, 2);
	return (1);
}

int	syntax_error(t_shell *shell)
{
	shell->exit_return = 258;
	write(2, RED "minishell: ", 18);
	ft_putstr_fdnl("syntax error in command line" RESET, 2);
	return (1);
}

int	error_wrong_path(t_shell *shell)
{
	shell->exit_return = 1;
	write(2, RED "minishell: ", 19);
	ft_putstr_fdnl(RED "No such file or directory" RESET, 2);
	return (1);
}
