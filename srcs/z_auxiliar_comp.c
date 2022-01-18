/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_auxiliar_comp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 16:19:34 by albzamor          #+#    #+#             */
/*   Updated: 2022/01/18 20:23:51 by albzamor         ###   ########.fr       */
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