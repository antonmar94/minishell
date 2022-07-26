/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 16:33:27 by antonmar          #+#    #+#             */
/*   Updated: 2022/07/26 18:45:57 by antonmar         ###   ########.fr       */
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
	shell->command_plus_args = NULL;
	shell->command = NULL;
	shell->command_flag = NULL;
	return (shell);
}

t_env_list	*env_var_list_new(char *env_var)
{
	t_env_list	*env_list;

	env_list = (t_env_list *)malloc(sizeof(t_env_list));
	if (!env_list)
		return (NULL);
	env_list->var_name = cut_env_var_name(env_var);
	env_list->var_content = cut_env_var_content(env_var);
	env_list->next = NULL;
	return (env_list);
}

char	**create_env_matrix(t_shell *shell, char **envp)
{
	t_env_list	*holder_first;
	char		*aux_envp;
	char		**minishell_envp;
	int			i;

	i = 0;
	aux_envp = NULL;
	holder_first = shell->env_list;
	minishell_envp = malloc (sizeof(char *) * (size_matriz(envp) + 1));
	while (holder_first)
	{
		aux_envp = ft_strjoin(holder_first->var_name, "=");
		minishell_envp[i] = ft_strjoin(aux_envp, holder_first->var_content);
		new_free(&aux_envp);
		holder_first = holder_first->next;
		i++;
	}
	minishell_envp[i] = NULL;
	return (minishell_envp);
}
