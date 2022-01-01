/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 17:11:21 by antonmar          #+#    #+#             */
/*   Updated: 2022/01/01 13:41:23 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_shell *initialice()
{
	t_shell *shell;
	shell = malloc(sizeof(t_shell));
	shell->line = NULL;
	shell->size_c = 2;//Numero de comandos actualizar al final
	shell->commands = malloc(sizeof(char*) * shell->size_c);
	shell->commands[0]="pwd";
	shell->commands[1]="exit";
	return (shell);
}

int main()
{
	t_shell *shell;
	shell = initialice();

	header();
	read_history(NULL);// si es null coje historial ~/.history
	//add_history(line);
	//printf("MINISHELL\n");
	while(1)
	{
		//imprimir prompt con la ruta:
		//readline() //capturar linea comandos
		shell->line =readline(BLUE"\nAlicornioPrompt$ "RESET);
		//printf(RESET"el comando introucido es: %s\n"GREEN, line);
		if (shell->line && *shell->line)// sólo si exite y hay contenido
			add_history(shell->line);
		find_command(shell);
		//history readline

		//if (ft_strcmp(shell->line, "pwd") == 0) // comparar para cada comando. Hacer una tabla con todos¿?¿?
			//printDir();
		free(shell->line);

		write_history(NULL);
	}
	return (0);
}