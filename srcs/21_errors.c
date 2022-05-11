/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 11:50:06 by albzamor          #+#    #+#             */
/*   Updated: 2022/05/09 19:52:47 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void command_error(t_shell *shell, char *command)
{
	shell->exit_return = 127;
	write(2, RED "minishell: ", 18);
	if (command)
		write(2, command, ft_strlen(command));
	write(2, ": command not found\n" RESET, 24);
}

int identifier_enviro_error(t_shell *shell)
{
	shell->exit_return = 153;
	write(2, RED "minishell: ", 18);
	ft_putstr_fdnl("not a valid identifier" RESET, 2);
	return (1);
}

int syntax_error(t_shell *shell)
{
	shell->exit_return = 258;
	write(2, RED "minishell: ", 18);
	ft_putstr_fdnl("syntax error in command line" RESET, 2);
	return (1);
}

int error_system_pwd(t_shell *shell)
{
	shell->exit_return = 992;
	write(2, RED "minishell: ", 18);
	ft_putstr_fdnl(RED "error getting current working directory" RESET, 2);
	return (1);
}

int error_child_process(t_shell *shell)
{
	shell->exit_return = 67;
	write(2, RED "minishell: ", 18);
	ft_putstr_fdnl(RED "error cannot create child process" RESET, 2);
	return (1);
}

int error_number_args(t_shell *shell)
{
	shell->exit_return = 1;
	write(2, RED "minishell: ", 18);
	ft_putstr_fdnl(RED "error number of arguments invalid" RESET, 2);
	return (1);
}

int error_wrong_path(t_shell *shell)
{
	shell->exit_return = 1;
	write(2, RED "minishell: ", 18);
	ft_putstr_fdnl(RED "No such file or directory" RESET, 2);
	return (1);
}

int error_too_many_args(void)
{
	write(2, RED "minishell: ", 18);
	ft_putstr_fdnl(RED "error too many arguments" RESET, 2);
	return (1);
}

int error_not_numeric(t_shell *shell)
{
	shell->exit_return = 255;
	write(2, RED "minishell: ", 18);
	if (*shell->command_args)
		write(2, *shell->command_args , ft_strlen(*shell->command_args));
	ft_putstr_fdnl(RED ": numeric argument required" RESET, 2);
	return (1);
}

int fd_error(t_shell *shell)
{
	shell->exit_return = 9;
	write(2, RED "minishell: ", 18);
	ft_putstr_fdnl(RED "bad file descriptor" RESET, 2);
	return (1);
}