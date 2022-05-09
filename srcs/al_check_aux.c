/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   al_check_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 14:10:35 by albzamor          #+#    #+#             */
/*   Updated: 2022/05/09 20:31:19 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_envar(t_shell *shell)
{
	if(shell->env_list->var_name)
			printf(GREEN"\nENVAR RECIBIDAS ✅\n"RESET);
		else
		{
			printf(RED"\nVARIABES DE ENTORNO NO RECIBIDAS ❌\n"RESET);
			exit(0);
		}
}