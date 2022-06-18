/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   22_errors_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 18:39:41 by albzamor          #+#    #+#             */
/*   Updated: 2022/06/18 16:41:51 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_error_child(t_shell *shell, int pid)
{
	if (pid < 0)
	{
		ft_error(shell, "", 67);
		return (1);
	}
	return (0);
}

int	error_not_numeric(t_shell *shell)
{
	shell->exit_return = 255;
	write(2, RED "minishell: ", 18);
	if (*shell->command_args)
		write(2, *shell->command_args, ft_strlen(*shell->command_args));
	ft_putstr_fdnl(RED ": numeric argument required" RESET, 2);
	return (1);
}

int	fd_error(t_shell *shell)
{
	shell->exit_return = 9;
	write(2, RED "minishell: ", 18);
	ft_putstr_fdnl(RED "bad file descriptor" RESET, 2);
	return (1);
}

int	error_too_many_args(void)
{
	write(2, RED "minishell: ", 18);
	ft_putstr_fdnl(RED "error too many arguments" RESET, 2);
	return (1);
}
