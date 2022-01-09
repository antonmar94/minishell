/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 12:16:27 by albzamor          #+#    #+#             */
/*   Updated: 2022/01/02 12:33:40 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int print_pwd(void)
{
	char pwd[1024];
	;
	if(!getcwd(pwd, sizeof(pwd)))
		return (error_system_pwd());
	printf("%s>\n", pwd);
	return (0);
}

int cd(t_shell *shell)
{
	int ret = 0;


	if(shell->size_line > 2 )
		return (error_number_args());
	if(shell->size_line == 1 ||
		(shell->size_line == 2 && ft_strcmp(shell->command_plus_args[1], "~") == 0 ))
		ret = chdir(shell->path->home_user);
	else
		ret = chdir(shell->command_plus_args[1]);
	if (ret)
		return (error_wrong_path());
	//write(1, "\n", 1);
	return (0);
}

void exit_minishell(t_shell *shell)
{

	printf(YELLOW"%s", shell->path->user);
	printf(GREEN " thanks for using our:\n");
	printf(CYAN"█▀▄▀█ █ █▄░█ █ █▀ █░█ █▀▀ █░░ █░░\n");
	printf(YELLOW"█░▀░█ █ █░▀█ █ ▄█ █▀█ ██▄ █▄▄ █▄\n");
	printf(GREEN"     by Antonmar🐔 and Albzamor🏴‍☠️\n");
	shell->exit = 1;

}

void help(t_shell *shell)
{
	int i;

	i = -1;
	ft_putstr_fdnl(GREEN"Command's List: "RESET, 1);
	while (++i < shell->size_c)
	{
		//printf("%s\n",shell->list_commands[i]);
		write(1, shell->list_commands[i], ft_strlen(shell->list_commands[i]));
		write(1, "\n", 1);
	}
	ft_putstr_fd(GREEN"(Pipes are coming..)"RESET, 1);
	write(1, "\n", 1);
}

int echo(t_shell *shell)
{
	int i = -1;

	if(!shell->command_args)
	{
		if (shell->command_flag && ft_strcmp(shell->command_flag, "-n") == 0)
			return(0);
		write (1,"\n", 1);
		return(0);
	}

	else
	{
		while (shell->command_args && shell->command_args[++i])
		{
			ft_putstr_fd(shell->command_args[i], 1);
			if (shell->command_args[i + 1])
				write(1, " ", 1);
		}

		if (shell->command_flag && ft_strcmp(shell->command_flag, "-n") == 0)
			return(0);
		write(1, "\n", 1);
	}
	return (0);
}
