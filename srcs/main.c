/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 17:11:21 by antonmar          #+#    #+#             */
/*   Updated: 2022/01/05 16:43:20 by albzamor         ###   ########.fr       */
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
	while(1)
	{
		//imprimir prompt con la ruta:
		//readline() //capturar linea comandos
		shell->line =readline(BLUE"AlicornioPrompt$ "RESET);
		//printf(RESET"el comando introucido es: %s\n"GREEN, line);
		if (shell->line && *shell->line)// sólo si exite y hay contenido
			add_history(shell->line);
		split_line_to_command(shell);


		print_all(shell);// imprimir argumentos y todo para comprobar;


		find_command(shell);
		//history readline

		//if (ft_strcmp(shell->line, "pwd") == 0) // comparar para cada comando. Hacer una tabla con todos¿?¿?
			//printDir();
		free(shell->line);

		write_history(NULL);
	}
	return (0);
}