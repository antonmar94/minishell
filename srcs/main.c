/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 17:11:21 by antonmar          #+#    #+#             */
/*   Updated: 2022/01/03 17:16:46 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


t_path *init_path(t_shell *shell)
{

	shell->path->user = ft_strdup(getenv("USER"));
	shell->path->home = ft_strdup("/Users/");
	shell->path->home_user = ft_strjoin(shell->path->home, shell->path->user);
	return(shell->path);
}


t_shell *initialice()
{
	t_shell *shell;

	shell = malloc(sizeof(t_shell));
	shell->path = malloc(sizeof(t_path));
	shell->path = init_path(shell);
	shell->line = NULL;
	shell->size_c = 5;//Numero de comandos actualizar al final
	shell->list_commands = malloc(sizeof(char*) * shell->size_c);
	shell->list_commands[0]="pwd";
	shell->list_commands[1]="exit";
	shell->list_commands[2]="hello";
	shell->list_commands[3]="help";
	shell->list_commands[4]="cd";
	return (shell);
}

int main()
{
	t_shell *shell;
	shell = initialice();

	header(shell);
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
		split_line_to_command(shell);
		//printf("\ncommands: %s\n", shell->command);
		//printf("\nnumero commands: %d\n", shell->size_args);
		//printf("\narg 1: %s\n", shell->command_plus_args[1]);

		find_command(shell);
		//history readline

		//if (ft_strcmp(shell->line, "pwd") == 0) // comparar para cada comando. Hacer una tabla con todos¿?¿?
			//printDir();
		free(shell->line);

		write_history(NULL);
	}
	return (0);
}