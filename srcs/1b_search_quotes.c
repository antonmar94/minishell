/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1b_search_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 19:13:39 by antonmar          #+#    #+#             */
/*   Updated: 2022/01/27 20:24:28 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *line_without_command(t_shell *shell)
{
	int		count_until_space;
	int		i;
	char	*command;
	char	*no_command_line;

	count_until_space = 0;
	i = 0;
	command = shell->line;
	while (command != ' ' && *command)
	{
		count_until_space++;
		command++;
	}
	while (!ft_strncmp(shell->line, shell->list_commands[i], count_until_space)
		&& shell->list_commands[i])
		i++;
	if (!(shell->list_commands[i]))
	{
		command_error();
		return (-1);
	}
	no_command_line = command;
	shell->command = shell->list_commands[i];
	return (no_command_line);
}

void	arg_listing(t_shell *shell)
{
	char 	*args;
	char	*aux;

	args = line_without_command(shell);
	aux = args;
	while (aux)
	{
		if (*aux == "\"")
		{
			aux++;
			while (*aux != "\"")
				aux++;
			/*if (!(*aux))
				return (NULL);  //introduce " y hasta el primer espacio como primer argumento(como si de un caracter cualquiera se tratara)
			else
				return (aux);  //introduce lo que se encuentra entre comillas como primer argumento(ignorando los espacios)*/
		}
		aux++;
	}
}