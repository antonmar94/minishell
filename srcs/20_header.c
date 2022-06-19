/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   20_header.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 21:00:57 by albzamor          #+#    #+#             */
/*   Updated: 2022/06/19 19:56:03 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	wellcome_header(t_shell *shell)
{
	clear_console();
	if (shell->line == NULL)
		clear_console();
	print_header(shell, "wellcome to");
}

void	clear_console(void)
{
	printf("\033[H\033[J");
}

void	print_header(t_shell *shell, char *custom_head)
{
	printf(YELLOW"%s", shell->path->user);
	printf(GREEN " %s our:\n", custom_head);
	printf(CYAN"█▀▄▀█ █ █▄░█ █ █▀ █░█ █▀▀ █░░ █░░\n");
	printf(YELLOW"█░▀░█ █ █░▀█ █ ▄█ █▀█ ██▄ █▄▄ █▄\n");
	printf(GREEN"     by Antonmar🏴‍☠️ and Albzamor🐔\n"RESET);
}
