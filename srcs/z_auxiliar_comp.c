/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_auxiliar_comp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 16:19:34 by albzamor          #+#    #+#             */
/*   Updated: 2022/02/03 19:12:11 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_all(t_shell *shell)
{
	int j = -1;

	if (shell->size_line)
		printf("\nline's word number: %d\n", shell->size_line);//palabras linbe
	if(shell->size_args)
		printf("\nnumero args: %d\n", shell->size_args);

	if (shell->command)
		printf(GREEN"\ncommand: %s\n"RESET, shell->command);// comando
	else
		printf(RED"\nNO command\n"RESET);
	if (shell->command_flag)
		printf("\nflag: %s\n", shell->command_flag);// flag
	else
		printf(RED"\nNO flag\n"RESET);
	if(shell->command_args)
	{
		while ( ++j < shell->size_args)//imprime solo args
			printf("\narg[%d] %s\n", j, shell->command_args[j] );
	}
	else
		printf(RED"\nNO arguments\n"RESET);

	printf(GREEN"\nEJECUTE:\n"RESET);

}

void	print_env_list(t_env_list *envp)
{

	t_env_list *copy;
	int i;

	i = 0;
	copy = envp;
	while (copy->next)
	{
		printf(BLUE"\nvar name:"RESET);
		printf("%s", copy->var_name);
		printf(GREEN"\nvar content:"RESET);
		printf("%s"RESET, copy->var_content);
		printf("\n");
		copy = copy->next;
		i++;
	}
	i++;
	printf(BLUE"\nvar name:"RESET);
	printf("%s", copy->var_name);
	printf(GREEN"\nvar content:"RESET);
	printf("%s"RESET, copy->var_content);
	printf("\n");
	printf(RED"tamaño lista: %d\n"RESET,i);
}

int	size_matriz(char **str)
{
	char **aux;
	int i;

	i=0;

	aux = str;
	while (*aux)
	{
		aux ++;
		i++;
	}
	return(i);


	/* int i;
	i = 0;
	while (str[i])
		i++;
	return(i); */
}

/* de la linea pasada (readline) comando a command y primer argumento sin tener
en cuenta errores ni ninguna otra cosa para testear export*/
void	easy_test_line_for_check_export(t_shell *shell)
{
	split_line_to_command(shell);
	//primer argumento: shell->command_args[0]

}