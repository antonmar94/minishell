/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 17:11:21 by antonmar          #+#    #+#             */
/*   Updated: 2022/05/09 20:28:43 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	leaks(void)
{
	system("leaks minishell");
}

int	main(int argc, char **argv, char** envp)
{
	(void)argv;
	t_shell	*shell;
	int		error;
	
	char	*contenido;

	contenido =	NULL;
	if (argc != 1)
	{
		error_too_many_args();
		exit(7);
	}
	shell = initialice(envp);
	//wellcome_header(shell);
	read_history(".history_own");
	//fprintf(stderr, "%i", 42);
	while(!shell->exit)
	{
		error = 0;
		shell->line = readline(BLUE"AlicornioPrompt$ "RESET);
		
		if (shell->line && *shell->line)
			add_history(shell->line);
		error = check_syntax(shell);
		if (error == 0)
		{
			split_arguments(shell);
			if(!find_enviro_command(shell))
				child_execution(shell, envp);
			free_all_struct(shell);
			shell->exit_return = 0;
		}
	}
	//easy_test_line_for_check_export(shell);//SOLO TEST ENV EXPORT LISTA
	write_history(".history_own");
	exit (shell->exit_return);
}
