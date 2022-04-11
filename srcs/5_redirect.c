/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_redirect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 20:05:39 by albzamor          #+#    #+#             */
/*   Updated: 2022/04/11 13:56:40 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void redirect(char *look_for_redirect)
{
	int redirect_flag = 0;
	char *redirect_file = NULL;
	char *ptr = look_for_redirect;
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
		if(fd == -1)
    		fd_error();
		dup2(fd, 1);//NEW  1 dup te dice que se escriba aqui lo que necesite.
		// Hay que cerrar todos los ficheros// ojo que se duplican al haceer pipes y forks
		//Se cierran todos close!!
	}
	else if(redirect_flag == 2)
	{
		fd = open(redirect_file, O_WRONLY|O_CREAT|O_APPEND, 0664);
		if(fd == -1)
    		fd_error();
		dup2(fd, 1);//APPEND
	}
}

// 4. Sustitución del programa



/* int do_exec(char *buff, t_shell *shell)
{

	int pid = fork();
	// Crea un proceso hijo, reemplaza el programa en el proceso hijo
	if(0 == pid)
	{	
		do_redirect(buff);
		//shell->command_args = do_parse(buff);
		
		if(NULL != shell->command)
		{
			execve(shell->command, shell->command_args, shell->en);
			// Proceso de reemplazo
		}
		else
		{
			exit(-1);
			// Si ingresa un error de comando, salga del proceso
		}
			
	}	
	else
	{
		waitpid(pid, NULL, 0);
		// Espera a que salga el proceso hijo
	}
	
	return 0;
}
 */