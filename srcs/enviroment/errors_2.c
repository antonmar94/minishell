/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoniojose <antoniojose@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 18:39:41 by albzamor          #+#    #+#             */
/*   Updated: 2022/09/30 19:50:12 by antoniojose      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	error_permission(t_shell *shell, char *file)
{
	shell->exit_return = 13;
	write(2, RED "minishell: ", 18);
	if (file)
		write(2, file, ft_strlen(file));
	ft_putstr_fd(": permission denied\n" RESET, 2);
}
