/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 20:28:58 by albzamor          #+#    #+#             */
/*   Updated: 2022/10/04 21:10:50 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	find_enviro_command(t_shell *shell)
{
	int	i;

	i = -1;
	if (!shell->command || shell->has_pipes)
		return (0);
	while (++i < 8)
	{
		if (ft_strcmp(shell->command, shell->list_commands[i]) == 0)
		{
			execute_command(shell, i);
			return (1);
		}
	}
	return (0);
}

int	find_command(t_shell *shell)
{
	int	i;

	i = -1;
	while (++i < shell->size_c)
	{
		if (!shell->command)
			return (0);
		if (ft_strcmp(shell->command, shell->list_commands[i]) == 0)
		{
			execute_command(shell, i);
			return (1);
		}
	}
	return (0);
}

void	exec_my_minishell(t_shell *shell)
{
	int		n_open;

	if (search_var_coincident(shell, "SHLVL"))
	{
		n_open = ft_atoi(search_var_coincident(shell, "SHLVL"));
		n_open ++;
		unset_util("SHLVL", shell);
		export_util("SHLVL", ft_itoa(n_open), shell);
	}
	execve (shell->command, shell->command_plus_args, shell->minishell_envp);
}

void	execute_command(t_shell *shell, int i)
{
	if (i == 0)
		export(shell);
	else if (i == 1)
		env(shell);
	else if (i == 2)
		unset(shell);
	else if (i == 3)
		wellcome_header(shell);
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
	else if (i == 9)
		exec_my_minishell(shell);
}

int	system_commmand(t_shell *shell, char **envp)
{
	int			ex_res;
	char		**env_aux;
	char		**paths_list;

	env_aux = envp;
	while (*env_aux && ft_strncmp(*env_aux, "PATH", 4))
		env_aux++;
	if (!*env_aux)
		command_error(shell, shell->command);
	*env_aux += 5;
	paths_list = ft_split(*env_aux, ':');
	ex_res = 0;
	while (*shell->command_plus_args && *paths_list)
	{
		ex_res = execve (shell->command, shell->command_plus_args, envp);
		if (ex_res < 0)
			ex_res = execve (ft_strjoin(ft_strjoin(*paths_list, "/"),
						shell->command), shell->command_plus_args, envp);
		paths_list++;
	}
	if (ex_res)
		return (0);
	return (1);
}
