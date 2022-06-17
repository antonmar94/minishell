/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 16:33:27 by antonmar          #+#    #+#             */
/*   Updated: 2022/06/17 19:26:24 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_path	*init_path(t_shell *shell)
{
	shell->path->user = ft_strdup(getenv("USER"));
	shell->path->home_user = ft_strjoin("/Users/", shell->path->user);
	return (shell->path);
}

void	init_list_command(t_shell *shell)
{
	shell->size_c = 9;
	shell->list_commands = malloc(sizeof(char *) * shell->size_c);
	shell->list_commands[0] = "export";
	shell->list_commands[1] = "env";
	shell->list_commands[2] = "unset";
	shell->list_commands[3] = "hello";
	shell->list_commands[4] = "exit";
	shell->list_commands[5] = "help";
	shell->list_commands[6] = "pwd";
	shell->list_commands[7] = "cd";
	shell->list_commands[8] = "echo";
}

t_shell	*initialice(char **envp)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	shell->exit = 0;
	shell->has_pipes = 0;
	shell->exit_return = 0;
	shell->size_com_args = 0;
	shell->path = malloc(sizeof(t_path));
	shell->path = init_path(shell);
	shell->env_list = init_list_env(shell, envp);
	shell->aux_p = malloc(sizeof(t_aux_p));
	init_list_command(shell);
	shell->pipes_struct = malloc(sizeof(t_pipes));
	shell->line = NULL;
	shell->line_walker = NULL;
	shell->command_args = NULL;
	shell->command = NULL;
	shell->command_flag = NULL;
	return (shell);
}
