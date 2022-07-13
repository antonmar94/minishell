/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 17:11:21 by antonmar          #+#    #+#             */
/*   Updated: 2022/07/13 22:12:42 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_interactive = 0;

void leaks()
{
	system("leaks minishell");
}

void	shell_execution(t_shell *shell, char **envp)
{

/*ESTO DEBE SER UNA FUNCION A PARTE, da mil millones de leaks*/

	t_env_list	*holder_first;
	char		*aux_envp;
	char		**free_aux_env;
	int			i;

	i = 0;
	aux_envp = NULL;
	holder_first = shell->env_list;
	free_aux_env = envp;
	while (holder_first)
	{
		aux_envp = ft_strjoin(holder_first->var_name, "=");
		envp[i] = ft_strjoin(aux_envp, holder_first->var_content);
		new_free(&aux_envp);
		holder_first = holder_first->next;
		i++;
	}
	envp[i] = NULL;

////////////////////////////////////////////

	shell->exit_return = 0;
	g_interactive = 1;
	shell->env_list_plus->next->var_content = ft_itoa(errno);
	shell->line = readline(CYAN"AlicornioPrompt$ "RESET);
	g_interactive = 0;
	if (!shell->line)
		exit(shell->exit_return);
	if (shell->line && *shell->line)
		add_history(shell->line);
	if (shell->line && !check_syntax(shell))
	{
		split_arguments(shell);
		if (!find_enviro_command(shell))
			child_execution(shell, envp);
	}
	free_all_struct(shell, envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	(void)argv;
	if (argc != 1)
		error_args_init();
	signal_handler();
	shell = initialice(envp);
	wellcome_header(shell);
	read_history(".history_own");
	while (!shell->exit)
		shell_execution(shell, envp);
	write_history(".history_own");
	atexit(leaks);
	exit(shell->exit_return);
}
