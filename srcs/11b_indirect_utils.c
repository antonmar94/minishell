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

char	*ask_for_line(t_shell *shell, char *all_files)
{
	char	*line_in;
	char	*clean_line;

	line_in = NULL;
	line_in = readline("> ");
	if (!line_in)
		printf("\n");
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

/* Obtener una matriz con la cantidad de heardocs a abrir
	y el nombre por el que se cierran */
char	**get_files_matrix(t_shell *shell, char *child_line, char *arrows)
{
	char	**all_files;
	int		matrix_size;
	int		elem_size;
	int		i;

	i = 0;
	matrix_size = get_matrix_size(child_line, arrows);
	all_files = (char **)malloc(sizeof(char *) * (matrix_size + 1));
	ft_memset(all_files, 0, matrix_size + 1);
	while (*child_line && i <= matrix_size)
	{
		elem_size = 0;
		if (!ft_strncmp(child_line, arrows, ft_strlen(arrows)))
		{
			
			child_line += ft_strlen(arrows);
			while (*child_line && *child_line == ' ')
				child_line++;
			all_files[i] = get_file_name(shell, child_line);
			i++;
		}
		child_line++;
	}
	all_files[i] = NULL;
	return (all_files);
}

int	get_clean_line(char **line, char *arrows)
{
	char	*arrow_finder;
	char	*aux_finder;
	int		line_size;

	arrow_finder = *line;
	line_size = 0;
	while (*arrow_finder)
	{
		if (!ft_strncmp(arrow_finder, arrows, ft_strlen(arrows)))
		{
			aux_finder = arrow_finder;
			aux_finder += ft_strlen(arrows);
			while (*aux_finder && *aux_finder == ' ')
				aux_finder++;
			while (*aux_finder && *aux_finder != ' '
					&& ft_strncmp(aux_finder, arrows, ft_strlen(arrows)))
				aux_finder++;
			//AQUI VA A HABER LEAKS
			*line = ft_substr(*line, 0, line_size);
			*line = ft_strjoin(*line, aux_finder);
			arrow_finder = *line;
			line_size = 0;
		}
		line_size++;
		arrow_finder++;
	}
	return (0);
}