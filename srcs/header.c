/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 21:00:57 by albzamor          #+#    #+#             */
/*   Updated: 2022/01/18 19:20:15 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	header(t_shell *shell)
{

	clear_console();
	print_header(shell);
	sleep(2);
	clear_console();

}

void	clear_console(void)
{
	printf("\033[H\033[J");
}

void	print_header(t_shell *shell)
{
	printf(YELLOW"%s", shell->path->user);
	printf(GREEN " wellcome to our:\n");
	printf(CYAN"█▀▄▀█ █ █▄░█ █ █▀ █░█ █▀▀ █░░ █░░\n");
	printf(YELLOW"█░▀░█ █ █░▀█ █ ▄█ █▀█ ██▄ █▄▄ █▄\n");
	printf(GREEN"     by Antonmar🐔 and Albzamor🏴‍☠️\n");
}
