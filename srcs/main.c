/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 17:11:21 by antonmar          #+#    #+#             */
/*   Updated: 2021/12/26 13:54:26 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char *line;

int main()
{
	line = NULL;
	header();
	read_history(NULL);// si es null coje historial ~/.history
	add_history(line);
	write_history(line);
	//printf("MINISHELL\n");
	while(1)
	{
		//imprimir prompt con la ruta:
		//readline() //capturar linea comandos
		line =readline(BLUE"AlicornioPrompt$ "RESET);
		printf(RESET"el comando introucido es: %s\n"GREEN, line);
		if (line && *line)// sólo si exite y hay contenido
			add_history(line);//history readline
		free(line);
		//sleep(1);
	}
	return (0);
}