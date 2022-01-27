/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 17:11:21 by antonmar          #+#    #+#             */
/*   Updated: 2022/01/27 18:53:53 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main()
{
	t_shell *shell;
	shell = initialice();

	header(shell);
	read_history(NULL);// si es null coje historial ~/.history
	//add_history(line);
	//printf("MINISHELL\n");
	while(!shell->exit)
	{
		shell->line =readline(BLUE"AlicornioPrompt$ "RESET);
		//printf(RESET"el comando introucido es: %s\n"GREEN, line);
		if (shell->line && *shell->line)// sólo si exite y hay contenido
			add_history(shell->line);
		split_line_to_command(shell);

		//print_all(shell);// imprimir argumentos y todo para comprobar;

		if (*shell->line)
			find_command(shell);


		//if (ft_strcmp(shell->line, "pwd") == 0) // comparar para cada comando. Hacer una tabla con todos¿?¿?
			//printDir();

		free_and_reset_values(shell);
		write_history(NULL);
	}
	return (0);
}

void	free_and_reset_values(t_shell *shell)
{
	if(shell->line)
			free(shell->line);
	shell->size_line = 0;
	shell->size_args = 0;
	shell->command = NULL;
}