/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_redirect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 20:05:39 by albzamor          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/04/23 12:04:44 by albzamor         ###   ########.fr       */
=======
/*   Updated: 2022/04/11 13:56:40 by albzamor         ###   ########.fr       */
>>>>>>> 807e1919f49adaf59306c91b8b1965e561cc7392
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

<<<<<<< HEAD
void do_redirect(t_shell *shell, char **envp)
{
	int redirect_flag = 0;
	char *redirect_file = NULL;
	char *ptr = shell->line;
=======
void redirect(char *look_for_redirect)
{
	int redirect_flag = 0;
	char *redirect_file = NULL;
	char *ptr = look_for_redirect;
>>>>>>> 807e1919f49adaf59306c91b8b1965e561cc7392
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
<<<<<<< HEAD
		dup2(fd, 1);
		execute_line(shell, envp);
=======
		if(fd == -1)
    		fd_error();
		dup2(fd, 1);//NEW  1 dup te dice que se escriba aqui lo que necesite.
		// Hay que cerrar todos los ficheros// ojo que se duplican al haceer pipes y forks
		//Se cierran todos close!!
>>>>>>> 807e1919f49adaf59306c91b8b1965e561cc7392
	}
	else if(redirect_flag == 2)
	{
		fd = open(redirect_file, O_WRONLY|O_CREAT|O_APPEND, 0664);
<<<<<<< HEAD
		dup2(fd, 1);
		execute_line(shell, envp);
=======
		if(fd == -1)
    		fd_error();
		dup2(fd, 1);//APPEND
>>>>>>> 807e1919f49adaf59306c91b8b1965e561cc7392
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
		execute_line(shell, envp);
}

