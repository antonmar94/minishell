/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   24_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 12:16:16 by albzamor          #+#    #+#             */
/*   Updated: 2022/06/16 17:15:15 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Señales, accion por defecto
				signal(SIGINT , SIG_DFL);
				signal(SIGQUIT, SIG_DFL); */

void	sigint_handler(int sig)
{
	signal(sig, sigint_handler);
	if (!interactive)
		return ;
	rl_redisplay();
	rl_replace_line("", 0);
	printf("\n");
	printf(BLUE"AlicornioPrompt$ "RESET);
}

void	sigquit_handler(int sig)
{
	char	*nbr;

	signal(sig, sigquit_handler);
	if (!interactive)
	{
		nbr = ft_itoa(sig);
		ft_putstr_fd("\nExit: ", 2);
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
