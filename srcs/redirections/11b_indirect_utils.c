/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11b_indirect_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 20:38:53 by antonmar          #+#    #+#             */
/*   Updated: 2022/09/24 11:37:02 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	last_num_arrows(char *line)
{
	while (*line)
		line++;
	line--;
	while (*line)
	{
		if (*line == '<')
		{
			line--;
			if (*line == '<')
				return (2);
			else
				return (1);
		}
		line--;
	}
	return (0);
}

int	check_interactive(t_shell *shell, char **line_in)
{
	if (g_interactive == 3)
	{
		if (*line_in)
			shell->sig_int_line = ft_strdup(*line_in);
		else
			exit (1);
		free(*line_in);
		return (1);
	}
	return (0);
}

int	get_matrix_size(char *line, char *arrows)
{
	char	*aux_line;
	int		matrix_size;

	matrix_size = 0;
	aux_line = line;
	while (*aux_line && *aux_line)
	{
		if (!ft_strncmp(aux_line, arrows, ft_strlen(arrows)))
			matrix_size++;
		aux_line++;
	}
	return (matrix_size);
}

char	*get_file_name(t_shell *shell, char *child_line)
{
	int		elem_size;
	char	*file_name;
	char	*aux_line;

	elem_size = 0;
	file_name = NULL;
	aux_line = child_line;
	while (*aux_line && *aux_line != ' ' && *aux_line != '<')
	{
		aux_line++;
		elem_size++;
	}
	aux_line = ft_substr(child_line, 0, elem_size);
	if (aux_line)
		file_name = arg_creator(shell, &aux_line);
	return (file_name);
}
