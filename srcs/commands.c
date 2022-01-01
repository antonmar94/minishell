/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 12:16:27 by albzamor          #+#    #+#             */
/*   Updated: 2022/01/01 14:02:24 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void printDir(void)
{
	char cwd[1024];
	getcwd(cwd, sizeof(cwd));
	printf("%s>", cwd);
}

void command_error(t_shell *shell)
{
	ft_putstr_fd("Minishell: Comando no encontrado: ", 1);
	printf("%s", shell->line);
}

void execute_command(t_shell *shell, int i)
{
	(void)shell;
	if (i == 0)
		printDir();
	else if (i == 1)
		exit(0);
}

void find_command(t_shell *shell)
{
	int i;

	i = -1;

	while (++i < shell->size_c)
	{
		if (ft_strcmp(shell->line, shell->commands[i]) == 0)
		{
			execute_command(shell, i);
			return;
		} // comparar para cada comando. Hacer una tabla con todos¿?¿?
	}
	command_error(shell);


}


