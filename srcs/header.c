/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 21:00:57 by albzamor          #+#    #+#             */
/*   Updated: 2022/01/01 12:21:28 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	header(void)
{
	char *user;

	user = getenv("USER");//get user
	clear_console();
	printf(YELLOW"%s", user);
	printf(GREEN " bienvenido a nuestra:\n");
	printf(CYAN"█▀▄▀█ █ █▄░█ █ █▀ █░█ █▀▀ █░░ █░░\n");
	printf(YELLOW"█░▀░█ █ █░▀█ █ ▄█ █▀█ ██▄ █▄▄ █▄\n");
	printf(GREEN"     by Antonmar🐔 and Albzamor🏴‍☠️\n");
	sleep(2);
	clear_console();

}

void	clear_console(void)
{
	printf("\033[H\033[J");
}

