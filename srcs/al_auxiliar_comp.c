/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   al_auxiliar_comp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 16:19:34 by albzamor          #+#    #+#             */
/*   Updated: 2022/06/03 19:16:07 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_all(t_shell *shell)
{
	int	j;

	j = -1;
	if (shell->size_com_args)
		printf("\nline's word number: %d\n", shell->size_com_args);
	if (shell->size_com_args)
		printf("\nnumero args: %d\n", shell->size_com_args);
	if (shell->command)
		printf(GREEN"\ncommand: %s\n"RESET, shell->command);
	else
		printf(RED"\nNO command\n"RESET);
	if (shell->command_flag)
		printf("\nflag: %s\n", shell->command_flag);
	else
		printf(RED"\nNO flag\n"RESET);
	if (shell->command_args)
	{
		while (++j < shell->size_com_args)
			printf("\narg[%d] %s\n", j, shell->command_args[j]);
	}
	else
		printf(RED"\nNO arguments\n"RESET);
	printf(GREEN"\nEJECUTE:\n"RESET);
}

void	print_env_list(t_env_list *envp)
{
	t_env_list	*copy;
	int			i;

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

void	printvar_content_text(char *var_name, char *var_content, t_shell *shell)
{
	char	*mod;
	char	*added;
	char	*text;

	mod = BLUE"modified."RESET;
	added = GREEN"added."RESET;
	if (look_for_var_name(shell, var_name))
		text = mod;
	else
		text = added;
	printf("Variable: ");
	printf(CYAN"%s "RESET, var_name);
	printf("with content: ");
	printf(CYAN"%s     "RESET, var_content);
	printf("%s\n", text);
}

void	print_var_unset(char *var_name, t_shell *shell)
{
	char	*mod;
	char	*added;
	char	*text;

	mod = GREEN"unset."RESET;
	added = RED"variable not found"RESET;
	if (look_for_var_name(shell, var_name))
		text = mod;
	else
		text = added;
	printf("Variable: ");
	printf(CYAN"%s "RESET, var_name);
	printf("     status:   ");
	printf("%s\n", text);
}

int	size_matriz(char **str)
{
	char	**aux;
	int		i;

	i = 0;
	aux = str;
	while (*aux)
	{
		aux ++;
		i++;
	}
	return (i);
}
