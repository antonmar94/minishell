/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_list_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 13:25:26 by albzamor          #+#    #+#             */
/*   Updated: 2022/01/03 13:37:29 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* split the read line into command (first) and args (rest) */
void	split_line_to_command(t_shell *shell)
{

	shell->size_args = ft_wordcount(shell->line, ' ') -1;
	shell->command_plus_args = ft_split(shell->line, ' ');
	shell->command = shell->command_plus_args[0];

}