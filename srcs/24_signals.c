/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   24_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 12:16:16 by albzamor          #+#    #+#             */
/*   Updated: 2022/07/27 21:54:41 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sigint_handler(int sig)
{
	//sig = 0;
	//signal(sig, sigint_handler);
/* 	if (!g_interactive)
		return ; */
	//printf("EL SIG QUE ENTRA ES ESTE [%d]\n",sig);
 	if ((sig == SIGINT || sig == SIGQUIT) && g_interactive != 2)
	{ 
		sig = 42;
		g_interactive = 0;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		errno = 1;
		return ;
	}
	else if (sig != 42)
	{
		g_interactive = 0;
		errno = 1;
		exit(errno);
	}
}

void	sigquit_handler(int sig)
{
	char	*nbr;

	if (g_interactive == 0)
	{
		nbr = ft_itoa(sig);
		ft_putendl_fd(nbr, 2);
		free(nbr);
		return ;
	}
	if (g_interactive == 1)
	{
		g_interactive = 0;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signal_handler(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
