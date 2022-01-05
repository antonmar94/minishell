/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 11:50:06 by albzamor          #+#    #+#             */
/*   Updated: 2022/01/05 19:29:49 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void command_error(void)
{
	ft_putstr_fdnl(RED"Minishell: Command not found "RESET, 2);
	//printf("%s", shell->line);
	//write(1, "\n", 1);
}

int	error_system_pwd(void)
{
	ft_putstr_fdnl(RED"Error getting current work directory"RESET, 2);
	return (1);
}

int	error_number_args(void)
{
	ft_putstr_fdnl(RED"Error number of arguments invalid"RESET, 2);
	return (1);
}

int	error_wrong_path(void)
{
	ft_putstr_fdnl(RED"Error path incorrect"RESET, 2);
	return (1);
}