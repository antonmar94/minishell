/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_evaluate_commands.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 20:28:58 by albzamor          #+#    #+#             */
/*   Updated: 2022/05/09 18:52:13 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int find_enviro_command(t_shell *shell)
{
	int i;

	i = -1;
	if(!shell->command)
		return(0);
	while (++i < 6)
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

int find_command(t_shell *shell)
{
	int i;

	i = -1;
	while (++i < shell->size_c)
	{
		if (!shell->command)
			return (0);
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
		export(shell);
	else if (i == 1)
		env(shell);
	else if (i == 2)
		unset(shell);
	else if (i == 3)
		wellcome_header(shell);//hello
	else if (i == 4)
		exit_minishell(shell);
	else if (i == 5)
		help(shell);	
	else if (i == 6)
		print_pwd(shell);
	else if (i == 7)
		cd(shell);
	else if (i == 8)
		echo(shell);
}

int system_commmand(t_shell *shell, char **envp)
{
	int 		ex_res;
	char		*env_aux;
	char		*env_dup;
	char		**paths_list;
	int			i;

	i = 0;
	env_aux = *envp;
	while (ft_strncmp(env_aux, "PATH", 4))
		env_aux++;
	env_dup = ft_strdup(env_aux);
	env_dup += 5;
	paths_list = ft_split(env_dup, ':');
	ex_res = 0;
	while (*shell->command_plus_args && *paths_list)
	{
		ex_res = execve (ft_strjoin(ft_strjoin(*paths_list, "/"),
			shell->command), shell->command_plus_args, envp);
		paths_list++;
	}
	if(ex_res)
		return (0);
	return (1);
}
