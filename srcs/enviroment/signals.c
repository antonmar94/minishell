/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 12:16:16 by albzamor          #+#    #+#             */
/*   Updated: 2022/10/04 18:09:38 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sigint_handler(int sig)
{
	if ((sig == SIGINT || sig == SIGQUIT))
	{
		rl_replace_line("", 0);
		printf("\n");
		rl_redisplay();
		if (g_interactive != 0)
			printf("\r%-2s", CYAN"AlicornioPrompt$ "RESET);
		g_interactive = 3;
		return ;
	}
	else
	{
		printf("\33[2K\r");
		exit(1);
	}
}

void	sigquit_handler(int sig)
{
	char	*nbr;
	char	*output;

	nbr = ft_itoa(sig);
	output = NULL;
	if (g_interactive == 0)
	{
		nbr = ft_itoa(sig);
		output = ft_strjoin("Quit: ", nbr);
		ft_putendl_fd(output, 2);
		free(output);
		g_interactive = 1;
		free(nbr);
		return ;
	}
	signal(SIGQUIT, SIG_IGN);
}

void	siguser_handler(int sig)
{
	(void)sig;
	signal(SIGQUIT, SIG_IGN);
}

void	signal_handler(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	signal(SIGUSR1, siguser_handler);
}
