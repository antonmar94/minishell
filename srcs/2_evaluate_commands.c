/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_evaluate_commands.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 20:28:58 by albzamor          #+#    #+#             */
/*   Updated: 2022/04/11 13:31:36 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

int find_command(t_shell *shell)
{
	int i;

	i = -1;
	while (++i < shell->size_c)
	{
		if (ft_strcmp(shell->command, shell->list_commands[i]) == 0)
		{
			execute_command(shell, i);
			return(1);
		} // comparar para cada comando. Hacer una tabla con todos¿?¿?
	}
	return(0);
	//command_error(shell);
}

void execute_command(t_shell *shell, int i)
{
	if (i == 0)
		return;
	else if (i == 1)
		print_pwd();
	else if (i == 2)
		wellcome_header(shell);//hello
	else if (i == 3)
		help(shell);
	else if (i == 4)
		cd(shell);
	else if (i == 5)
		echo(shell);
	else if (i == 6)
		clear_console();
	else if (i == 7)
		export(shell);
	else if (i == 8)
		env(shell);
	else if (i == 9)
		unset(shell);
	else if (i == 10)
		exit_minishell(shell);
}

int system_commmand(t_shell *shell, char **envp)
{
	int ex_res;
	int pid;
	char	*env_aux;
	char	**paths_list;

	pid = fork();
	if (pid < 0)
		return (0);
	if(pid == 0)
	{
		env_aux = *envp;
		while (ft_strncmp(env_aux, "PATH", 4))
			env_aux++;
		env_aux += 5;
		paths_list = ft_split(env_aux, ':');
		while (*paths_list)
		{
			//redirect(shell->final_line);
			ex_res = execve (ft_strjoin(ft_strjoin(*paths_list, "/"),
				shell->command), shell->command_plus_args, envp);
			paths_list++;
		}
		if(ex_res)
			return (0);
	}
	waitpid(pid, NULL, 0);
	return (1);
}
