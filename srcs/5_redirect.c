/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_redirect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 20:05:39 by albzamor          #+#    #+#             */
/*   Updated: 2022/03/22 11:32:11 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void do_redirect(char *buff)
{
	int redirect_flag = 0;
	char *redirect_file = NULL;
	char *ptr = buff;

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
			{
				ptr++;
			}

			redirect_file = ptr;

			while(*ptr != ' ' && *ptr != '\0')
			{
				ptr++;
			}
				
			*ptr = '\0';
		}
		ptr++;
	}

	if(redirect_flag == 1)
	{
		int fd = open(redirect_file, O_WRONLY|O_CREAT|O_TRUNC, 0664);
		dup2(fd, 1);
	}
	else if(redirect_flag == 2)
	{
		int fd = open(redirect_file, O_WRONLY|O_CREAT|O_APPEND, 0664);
		dup2(fd, 1);
	}
}

// 4. Sustitución del programa
int do_exec(char *buff, t_shell *shell)
{


	int pid = fork();
	// Crea un proceso hijo, reemplaza el programa en el proceso hijo
	if(0 == pid)
	{	
		do_redirect(buff);
		//shell->command_args = do_parse(buff);
		
		if(NULL != shell->command)
		{
			execvp(shell->command, shell->command_args);
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
