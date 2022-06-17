/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   al_check_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 14:10:35 by albzamor          #+#    #+#             */
/*   Updated: 2022/06/04 19:12:44 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_envar(t_shell *shell)
{
	if (shell->env_list_plus->var_name)
		printf(GREEN"\nENVAR RECIBIDAS ✅\n"RESET);
	else
	{
		printf(RED"\nVARIABES DE ENTORNO NO RECIBIDAS ❌\n"RESET);
		exit(0);
	}
}
