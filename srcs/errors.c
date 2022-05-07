/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 11:50:06 by albzamor          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/04/23 10:02:24 by antonmar         ###   ########.fr       */
=======
/*   Updated: 2022/04/11 13:30:26 by albzamor         ###   ########.fr       */
>>>>>>> 807e1919f49adaf59306c91b8b1965e561cc7392
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void command_error(char *command)
{
	write(2, RED"minishell: ", 18);
	write(2, command, ft_strlen(command));
	write(2, ": command not found\n"RESET, 24);
}

int	syntax_error(void)
{
	ft_putstr_fdnl(RED"syntax error in command line"RESET, 2);
	return (1);
}

int	error_system_pwd(void)
{
	ft_putstr_fdnl(RED"error getting current work directory"RESET, 2);
	return (1);
}

int	error_child_process(void)
{
	ft_putstr_fdnl(RED"error cannot create child process"RESET, 2);
	return (1);
}

int	error_number_args(void)
{
	ft_putstr_fdnl(RED"error number of arguments invalid"RESET, 2);
	return (1);
}

int	error_wrong_path(void)
{
	ft_putstr_fdnl(RED"error path incorrect"RESET, 2);
	return (1);
}

int	error_too_many_args(void)
{
	ft_putstr_fdnl(RED"error too many arguments"RESET, 2);
	return(1);
}

int	error_not_numeric(void)
{
	ft_putstr_fdnl(RED"numeric argument required"RESET, 2);
	return(1);
}

int	fd_error(void)
{
	ft_putstr_fdnl(RED"fd error"RESET, 2);
	return (1);
}