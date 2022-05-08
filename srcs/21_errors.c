/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 11:50:06 by albzamor          #+#    #+#             */
/*   Updated: 2022/05/08 12:20:53 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void command_error(t_shell *shell, char *command)
{
	shell->exit_return = 127;
	write(2, RED "minishell: ", 18);
	write(2, command, ft_strlen(command));
	write(2, ": command not found\n" RESET, 24);
}

int syntax_error(t_shell *shell)
{
	shell->exit_return = 258;
	ft_putstr_fdnl(RED "syntax error in command line" RESET, 2);
	return (1);
}

int error_system_pwd(t_shell *shell)
{
	shell->exit_return = 992;
	ft_putstr_fdnl(RED "error getting current working directory" RESET, 2);
	return (1);
}

int error_child_process(t_shell *shell)
{
	shell->exit_return = 67;
	ft_putstr_fdnl(RED "error cannot create child process" RESET, 2);
	return (1);
}

int error_number_args(t_shell *shell)
{
	shell->exit_return = 1;
	ft_putstr_fdnl(RED "error number of arguments invalid" RESET, 2);
	return (1);
}

int error_wrong_path(t_shell *shell)
{
	shell->exit_return = 1;
	ft_putstr_fdnl(RED "No such file or directory" RESET, 2);
	return (1);
}

int error_too_many_args(void)
{
	ft_putstr_fdnl(RED "error too many arguments" RESET, 2);
	return (1);
}

int error_not_numeric(t_shell *shell)
{
	shell->exit_return = 255;
	ft_putstr_fdnl(RED "numeric argument required" RESET, 2);
	return (1);
}

int fd_error(t_shell *shell)
{
	shell->exit_return = 9;
	ft_putstr_fdnl(RED "bad file descriptor" RESET, 2);
	return (1);
}