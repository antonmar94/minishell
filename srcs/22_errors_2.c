/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   22_errors_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 18:39:41 by albzamor          #+#    #+#             */
/*   Updated: 2022/06/29 19:17:29 by antonmar         ###   ########.fr       */
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
	ft_putstr_fd(RED ": numeric argument required\n" RESET, 2);
	return (1);
}

int	fd_error(t_shell *shell)
{
	shell->exit_return = 9;
	write(2, RED "minishell: ", 18);
	ft_putstr_fd(RED "bad file descriptor\n" RESET, 2);
	return (1);
}

int	error_too_many_args(t_shell *shell)
{
	shell->exit_return = 1;
	write(2, RED "minishell: ", 18);
	ft_putstr_fd(RED "error too many arguments\n" RESET, 2);
	return (1);
}

void	error_args_init(void)
{
	write(2, RED "minishell: ", 18);
	ft_putstr_fd(RED "error too many arguments\n" RESET, 2);
	exit (1);
}
