/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   al_auxiliar_comp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 16:19:34 by albzamor          #+#    #+#             */
/*   Updated: 2022/05/08 18:55:59 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_all(t_shell *shell)
{
	int j = -1;

	if (shell->size_com_args)
		printf("\nline's word number: %d\n", shell->size_com_args);//palabras linbe
	if(shell->size_com_args)
		printf("\nnumero args: %d\n", shell->size_com_args);

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
		while ( ++j < shell->size_com_args)//imprime solo args
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
	printf(RED"\nsize enviroment: %d\n"RESET,i);
}

void print_var_content_text(char *var_name, char *var_content, t_shell *shell)
{
	char mod[]=BLUE"modified."RESET;
	char added[]=GREEN"added."RESET;
	char *text;
	if (look_for_var_name(shell, var_name))
		text=mod;
	else
		text=added;
	printf("Variable: ");
	printf(CYAN"%s "RESET, var_name);
	printf("with content: ");
	printf(CYAN"%s     "RESET, var_content);
	printf("%s\n", text);	
}

void print_var_unset(char *var_name, t_shell *shell)
{
	char mod[]=GREEN"unset."RESET;
	char added[]=RED"variable not found"RESET;
	char *text;
	if (look_for_var_name(shell, var_name))
		text=mod;
	else
		text=added;
	printf("Variable: ");
	printf(CYAN"%s "RESET, var_name);
	printf("     status:   ");
	printf("%s\n", text);	
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
/* void	easy_test_line_for_check_export(t_shell *shell)
{
	split_line_to_command(shell);
	//primer argumento: shell->command_args[0]

} */