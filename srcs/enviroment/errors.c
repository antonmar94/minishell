/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 11:50:06 by albzamor          #+#    #+#             */
/*   Updated: 2022/09/24 13:19:32 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_error(t_shell *shell, char *elem_err, int error_code)
{
	shell->exit_return = error_code;
	perror(ft_strjoin(RED"minishell: ", elem_err));
	return (1);
}

void	command_error(t_shell *shell, char *command)
{
	shell->exit_return = 127;
	errno = 127;
	write(2, RED "minishell: ", 18);
	if (command)
		write(2, command, ft_strlen(command));
	ft_putstr_fd(": command not found\n" RESET, 2);
}

int	identifier_enviro_error(t_shell *shell)
{
	shell->exit_return = 153;
	write(2, RED "minishell: ", 18);
	ft_putstr_fd("not a valid identifier\n" RESET, 2);
	return (1);
}

int	syntax_error(t_shell *shell)
{
	errno = 258;
	shell->exit_return = 258;
	write(2, RED "minishell: ", 18);
	ft_putstr_fd("syntax error in command line\n" RESET, 2);
	return (1);
}

int	error_wrong_path(t_shell *shell, char *file)
{
	shell->exit_return = 1;
	write(2, RED "minishell: ", 19);
	if (file)
		write(2, file, ft_strlen(file));
	ft_putstr_fd(RED ": No such file or directory\n" RESET, 2);
	return (1);
}
