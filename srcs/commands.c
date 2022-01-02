/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 12:16:27 by albzamor          #+#    #+#             */
/*   Updated: 2022/01/02 12:31:54 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int print_pwd(void)
{
	char pwd[1024];
	;
	if(!getcwd(pwd, sizeof(pwd)))
		return (error_system_pwd());
	printf("%s>", pwd);
	return (0);
}

void exit_minishell(void)
{
	char *user;

	user = getenv("USER");//get user
	printf(YELLOW"%s", user);
	printf(GREEN " thanks for using our:\n");
	printf(CYAN"█▀▄▀█ █ █▄░█ █ █▀ █░█ █▀▀ █░░ █░░\n");
	printf(YELLOW"█░▀░█ █ █░▀█ █ ▄█ █▀█ ██▄ █▄▄ █▄\n");
	printf(GREEN"     by Antonmar🐔 and Albzamor🏴‍☠️\n");
	//sleep(2);
	//clear_console();

	exit(0);
}



void execute_command(t_shell *shell, int i)
{
	(void)shell;
	if (i == 0)
		print_pwd();
	else if (i == 1)
		exit_minishell();
	else if (i == 2)
		header();
	else if (i == 3)
		help(shell);
}

void find_command(t_shell *shell)
{
	int i;

	i = -1;

	while (++i < shell->size_c)
	{
		if (ft_strcmp(shell->line, shell->commands[i]) == 0)
		{
			execute_command(shell, i);
			return;
		} // comparar para cada comando. Hacer una tabla con todos¿?¿?
	}
	command_error(shell);
}

void help(t_shell *shell)
{
	int i;

	i = -1;
	ft_putstr_fdnl(GREEN"Lista de comandos: "RESET, 1);
	while (++i < shell->size_c)
	{
		//printf("%s\n",shell->commands[i]);
		write(1, shell->commands[i], ft_strlen(shell->commands[i]));
		write(1, "\n", 1);
	}
	ft_putstr_fd(GREEN"(Pipes are coming..)"RESET, 1);
}


