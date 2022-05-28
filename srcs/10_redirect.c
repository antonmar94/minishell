/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 20:05:39 by albzamor          #+#    #+#             */
/*   Updated: 2022/05/28 13:57:53 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void do_redirect(t_shell *shell, char **envp)
{
	int redirect_flag = 0;
	char *redirect_file = NULL;
	char *ptr = shell->line;
	int fd;

	while(*ptr != '\0')
	{
		if(*ptr == '>')
		{
			*ptr++ = '\0';
			++redirect_flag;

			if(*ptr == '>')
			{
				++redirect_flag;
				ptr++;
			}
			
			while(*ptr == ' ' && *ptr != '\0')
				ptr++;

			redirect_file = ptr;

			while(*ptr != ' ' && *ptr != '\0')
				ptr++;
				
			*ptr = '\0';
		}
		ptr++;
	}
	if(redirect_flag == 1)
	{
		fd = open(redirect_file, O_WRONLY|O_CREAT|O_TRUNC, 0664);
		dup2(fd, 1);
		execute_child_line(shell, envp);
	}
	else if(redirect_flag == 2)
	{
		fd = open(redirect_file, O_WRONLY|O_CREAT|O_APPEND, 0664);
		dup2(fd, 1);
		execute_child_line(shell, envp);
	}
	/* else if(redirect_flag == 3)
	{
		int aux; // variable auxiliar para redirigir 
		aux = open (entrada , O_CREAT | O_RDONLY); 
		if(aux == -1){
			fprintf( stderr , "%s : Error. %s\n" , entrada , strerror(errno)); // Mostrar error , -1 igual a NULL 
			return 1;
		} else { 
			dup2(aux,fileno(stdin)); // Redirreccion de 0, Entrada estandar 
		}	
	}  */
	else
		execute_child_line(shell, envp);
}

