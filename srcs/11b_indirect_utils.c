/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11b_indirect_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 20:38:53 by antonmar          #+#    #+#             */
/*   Updated: 2022/09/10 15:38:57 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int last_num_arrows(char *line)
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

char	*ask_for_line(t_shell *shell, char *all_files)
{
	char	*line_in;
	char	*clean_line;

	line_in = NULL;
	line_in = readline("> ");
/* 	if (!line_in)
		printf("\n"); */
	if (line_in && ft_strcmp(all_files, line_in))
	{
		if (*line_in)
		{
			clean_line = arg_creator(shell, &line_in);
			new_free(&line_in);
			line_in = clean_line;
			line_in = ft_strjoin(line_in, "\n");
		}
		else
			line_in = ft_strdup("\n");
	}
	return (line_in);
}

int	get_matrix_size(char *line, char *arrows)
{
	char	*aux_line;
	int		matrix_size;

	matrix_size = 0;
	aux_line = line;
	while (aux_line && *aux_line)
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
