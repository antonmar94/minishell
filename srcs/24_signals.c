/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   24_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 12:16:16 by albzamor          #+#    #+#             */
/*   Updated: 2022/06/20 22:43:24 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sigint_handler(int sig)
{
	signal(sig, sigint_handler);
	if (!g_interactive)
		return ;
	rl_redisplay();
	rl_replace_line("", 0);
	printf("\n");
	printf(CYAN"AlicornioPrompt$ "RESET);
}

void	sigquit_handler(int sig)
{
	char	*nbr;

	signal(sig, sigquit_handler);
	if (!g_interactive)
	{
		nbr = ft_itoa(sig);
		ft_putendl_fd(nbr, 2);
		free(nbr);
		return ;
	}
	rl_on_new_line();
	rl_redisplay();
}

void	signal_handler(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}
