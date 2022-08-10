/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   24_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 12:16:16 by albzamor          #+#    #+#             */
/*   Updated: 2022/08/10 21:42:37 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sigint_handler(int sig)
{
	if ((sig == SIGINT || sig == SIGQUIT) && g_interactive != 2)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		printf("\n");
		rl_redisplay();
		errno = 1;
		return ;
	}
	else
	{
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
