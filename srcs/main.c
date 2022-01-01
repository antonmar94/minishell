/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 17:11:21 by antonmar          #+#    #+#             */
/*   Updated: 2022/01/01 11:58:16 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char *line;

void printDir()
{
	char cwd[1024];
	getcwd(cwd, sizeof(cwd));
	printf("\n%s>", cwd);
}

int main()
{
	line = NULL;
	header();
	read_history(NULL);// si es null coje historial ~/.history
	//add_history(line);
	//printf("MINISHELL\n");
	while(1)
	{
		//imprimir prompt con la ruta:
		//readline() //capturar linea comandos
		line =readline(BLUE"\nAlicornioPrompt$ "RESET);
		//printf(RESET"el comando introucido es: %s\n"GREEN, line);
		if (line && *line)// sólo si exite y hay contenido
			add_history(line);//history readline
		if (ft_strcmp(line, "pwd") == 0) // comparar para cada comando. Hacer una tabla con todos¿?¿?
			printDir();
		free(line);

	write_history(NULL);
	}
	return (0);
}