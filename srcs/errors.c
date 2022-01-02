/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 11:50:06 by albzamor          #+#    #+#             */
/*   Updated: 2022/01/02 12:23:47 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void command_error(t_shell *shell)
{
	ft_putstr_fd(RED"Minishell: Command not found: "RESET, 2);
	printf("%s", shell->line);
}

int	error_system_pwd(void)
{
	ft_putstr_fdnl(RED"Error getting current work directory"RESET, 2);
	return (1);
}