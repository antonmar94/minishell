/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 17:11:21 by antonmar          #+#    #+#             */
/*   Updated: 2022/06/17 20:54:53 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	interactive = 0;

void	leaks(void)
{
	system("leaks minishell");
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	(void)argv;
	if (argc != 1)
	{
		error_too_many_args();
		exit(7);
	}
	signal_handler();
	shell = initialice(envp);
	//wellcome_header(shell);
	read_history(".history_own");
	while (!shell->exit)
	{
		shell->exit_return = 0;
		interactive = 1;
		errno = 0;
		shell->line = readline(BLUE"AlicornioPrompt$ "RESET);
		interactive = 0;
		
		if (!shell->line)
			exit(shell->exit_return);
		if (shell->line && *shell->line)
			add_history(shell->line);
		
		if (shell->line && !check_syntax(shell))
		{
			split_arguments(shell);
			if (!find_enviro_command(shell))
				child_execution(shell, envp);
			//free_all_struct(shell);
		}
		free_all_struct(shell);
		//leaks();
		//atexit(leaks);
	}
	write_history(".history_own");
	exit(shell->exit_return);
}
