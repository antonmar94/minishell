/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_indirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 20:37:28 by antonmar          #+#    #+#             */
/*   Updated: 2022/08/29 15:41:02 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	indirect_files(t_shell *shell, char **all_files)
{
	int		num_arrows;

	num_arrows = check_redirect(&shell->line, all_files, '<');
	if (num_arrows)
	{
		get_line_execute(&shell->line, all_files, '<');
		num_arrows = get_in_files(shell, all_files, num_arrows);
		*all_files = arg_creator(shell, all_files);
		if (**all_files == '>')
			return (syntax_error(shell));
		if (num_arrows == 1 && access(*all_files, R_OK) < 0)
		{
			ft_error(shell, *all_files, 1);
			return (0);
		}
	}
	return (num_arrows);
}

char	*ask_for_line(t_shell *shell, /* int *fd,  */char *all_files)
{
	char	*line_in;
	char	*clean_line;

	line_in = NULL;
	line_in = readline("> ");
	if (ft_strcmp(all_files, line_in))
	{
		clean_line = arg_creator(shell, &line_in);
		new_free(&line_in);
		line_in = clean_line;
	}
	return (line_in);
}

/* Obtener las lineas introducidas por el usuario
	juntandolas todas en "all_lines" */
char	*two_arrows(t_shell *shell, char **all_files)
{
	char	*line_in;
	char	*all_lines;

	//line_in = NULL;
	all_lines = NULL;
	kill(shell->pipes_struct->pid, SIGUSR1);
	line_in = ask_for_line(shell, *all_files);
	if (line_in && !ft_strcmp(*all_files, line_in))
		all_files++;
	else if (line_in)
		all_lines = ft_strjoin(line_in, "\n");
	else
		all_lines = "\n";
	while (*all_files)
	{
		new_free(&line_in);
		line_in = ask_for_line(shell, *all_files);
		if (line_in && !ft_strcmp(*all_files, line_in))
			all_files++;
		else if (line_in)
			all_lines = ft_strjoin(all_lines, ft_strjoin(line_in, "\n"));
		else
			all_lines = ft_strjoin(all_lines, "\n");
	}
	return (all_lines);
}

int	do_indirect(t_shell *shell)
{
	int		num_arrows;
	char	*all_files;
	int		fd;

	all_files = NULL;
	num_arrows = indirect_files(shell, &all_files);
	if (num_arrows == 1 && !shell->exit_return)
	{
		fd = open(all_files, O_RDONLY);
		if (fd < 0)
			error_wrong_path(shell);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	return (0);
}

int	get_matrix_size(char *line)
{
	char	*aux_line;
	int		matrix_size;

	matrix_size = 0;
	aux_line = line;
	while (aux_line && *aux_line)
	{
		if (!ft_strncmp(aux_line, "<<", 2))
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
char	**get_files_matrix(t_shell *shell, char *child_line)
{
	char	**all_files;
	int		matrix_size;
	int		elem_size;
	int		i;

	i = 0;
	matrix_size = get_matrix_size(child_line);
	all_files = (char **)malloc(sizeof(char *) * (matrix_size + 1));
	ft_memset(all_files, 0, matrix_size + 1);
	while (*child_line && i <= matrix_size)
	{
		elem_size = 0;
		if (!ft_strncmp(child_line, "<<", 2))
		{
			child_line += 2;
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

int	get_clean_line(t_pipes	*pipes_struct)
{
	char	*arrow_finder;
	char	*aux_finder;
	int		line_size;

	arrow_finder = pipes_struct->child_line;
	line_size = 0;
	while (*arrow_finder)
	{
		if (!ft_strncmp(arrow_finder, "<<", 2))
		{
			aux_finder = arrow_finder;
			aux_finder += 2;
			while (*aux_finder && *aux_finder == ' ')
				aux_finder++;
			while (*aux_finder && *aux_finder != ' ' && ft_strncmp(aux_finder, "<<", 2))
				aux_finder++;
			pipes_struct->child_line = ft_substr(pipes_struct->child_line, 0, line_size);
			pipes_struct->child_line = ft_strjoin(pipes_struct->child_line, aux_finder);
			arrow_finder = pipes_struct->child_line;
			line_size = 0;
		}
		line_size++;
		arrow_finder++;
	}
	return (0);
}

int	double_indirect(t_shell *shell)
{
	t_pipes	*pipes_struct;

	pipes_struct = shell->pipes_struct;
	pipes_struct->all_files = get_files_matrix(shell, pipes_struct->child_line);
	get_clean_line(pipes_struct);
	if (*pipes_struct->all_files)
		pipes_struct->heardoc_lines = two_arrows(shell, pipes_struct->all_files);
	return (0);
}
