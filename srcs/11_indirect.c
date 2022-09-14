/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_indirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 20:37:28 by antonmar          #+#    #+#             */
/*   Updated: 2022/09/14 21:01:45 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Obtener una matriz con la cantidad de heardocs a abrir
	y el nombre por el que se cierran */
char	**get_files_matrix(t_shell *shell, char *child_line, char *arrows)
{
	char	**all_files;
	int		matrix_size;
	int		i;

	i = 0;
	matrix_size = get_matrix_size(child_line, arrows);
	all_files = (char **)malloc(sizeof(char *) * (matrix_size + 1));
	ft_memset(all_files, 0, matrix_size + 1);
	while (*child_line && i <= matrix_size)
	{
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
	char	*line_aux;
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
			line_aux = *line;
			*line = ft_substr(line_aux, 0, line_size);
			free(line_aux);
			line_aux = *line;
			*line = ft_strjoin(line_aux, aux_finder);
			free(line_aux);
			arrow_finder = *line;
			line_size = 0;
		}
		line_size++;
		arrow_finder++;
	}
	return (0);
}

/* Obtener las lineas introducidas por el usuario
	juntandolas todas en "all_lines" */
char	*two_arrows(t_shell *shell, char **all_files)
{
	char	*line_in;
	char	*all_lines;
	char	*free_aux;

	all_lines = NULL;
	kill(shell->pipes_struct->pid, SIGUSR1);
	line_in = ask_for_line(shell, *all_files);
 	if (line_in && !ft_strcmp(*all_files, line_in))
	 {
		free_aux = *all_files;
		all_files++;
		free(free_aux);
	 }
	else if (line_in)
		all_lines = ft_strdup(line_in);
	if (g_interactive == 3)
		return (NULL);
	while (line_in && all_files && *all_files)
	{
		//AQUI VA A HABER LEAKS
		new_free(&line_in);
		line_in = ask_for_line(shell, *all_files);
		if (g_interactive == 3)
			return (NULL);
		if (line_in && !ft_strcmp(*all_files, line_in))
		{
			free_aux = *all_files;
			all_files++;
			free(free_aux);
		}
		else if (line_in)
		{
			free_aux = all_lines;
			all_lines = ft_strjoin(all_lines, line_in);
			free(free_aux);
		}
		leaks();
	}
	return (all_lines);
}

int	do_indirect(t_shell *shell)
{
	t_pipes	*pipes_struct;
	char	**last_file;
	char	**files_matrix;
	char	*start_line;

	//esto debe quitarse
	files_matrix = NULL;
	pipes_struct = shell->pipes_struct;
	start_line = shell->line;
	//files_matrix = get_files_matrix(shell, start_line, "<");
	pipes_struct->simple_files = files_matrix;
	get_clean_line(&shell->line, "<");
	if (pipes_struct->last_arrows == 1)
	{
		files_matrix = get_files_matrix(shell, start_line, "<");
		if (pipes_struct->all_files)
			free(pipes_struct->all_files);
		pipes_struct->all_files = files_matrix;
		//AQUI VA A HABER LEAKS
		last_file  = pipes_struct->all_files;
		while(last_file[1])
			last_file++;
		pipes_struct->all_files = last_file;
	}
	return (0);
}

int	double_indirect(t_shell *shell)
{
	t_pipes	*pipes_struct;

	pipes_struct = shell->pipes_struct;
	pipes_struct->last_arrows = last_num_arrows(pipes_struct->child_line);
	if (shell->pipes_struct->all_files)
		free(shell->pipes_struct->all_files);
	pipes_struct->all_files = get_files_matrix(shell, pipes_struct->child_line, "<<");
	get_clean_line(&pipes_struct->child_line, "<<");
	if (*pipes_struct->all_files)
		pipes_struct->heardoc_lines = two_arrows(shell, pipes_struct->all_files);
	if (g_interactive == 3)
	{
		g_interactive = 0;
		return (-1);
	}
	return (0);
}
