/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 17:11:21 by antonmar          #+#    #+#             */
/*   Updated: 2022/09/24 17:51:36 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_interactive = 0;

void	shell_execution(t_shell *shell)
{
	shell->minishell_envp = create_env_matrix(shell);
	shell->env_list_plus->next->var_content = ft_itoa(errno);
	ft_new_line(shell);
	if (!shell->line)
		exit(shell->exit_return);
	if (shell->line && *shell->line)
		add_history(shell->line);
	if (shell->line && !check_syntax(shell))
	{
		split_arguments(shell);
		if (!find_enviro_command(shell))
			child_execution(shell, shell->minishell_envp);
	}
	free_all_struct(shell, shell->minishell_envp);
	free_matrix(shell->minishell_envp);
	free(shell->minishell_envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	if (*envp == NULL)
	{
		write(2, "NOT FOUND ENV", 14);
		return 0;
	}
	(void)argv;
	if (argc != 1)
		error_args_init();
	signal_handler();
	shell = initialice(envp);
	wellcome_header(shell);
	read_history(".history_own");
	while (!shell->exit)
		shell_execution(shell);
	write_history(".history_own");
	exit(shell->exit_return);
}
