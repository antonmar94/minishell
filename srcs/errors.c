/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 11:50:06 by albzamor          #+#    #+#             */
/*   Updated: 2022/03/09 11:18:50 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void command_error(void)
{
	ft_putstr_fdnl(RED"Minishell: Command not found "RESET, 2);
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