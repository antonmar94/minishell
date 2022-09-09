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
	if (!line_in)
		line_in = "";
	return (line_in);
}

/* Obtener las lineas introducidas por el usuario juntandolas todas en "all_lines" */
char	*two_arrows(t_shell *shell, char **all_files)
{
	char	*line_in;
	char	*all_lines;

	line_in = NULL;
	kill(shell->pipes_struct->pid, SIGUSR1);
	line_in = ask_for_line(shell, *all_files);
	all_lines = ft_strjoin(line_in, "\n");
	while (*all_files /* && errno != 1 */)
	{
		new_free(&line_in);
		line_in = ask_for_line(shell, *all_files);
		if (line_in && !ft_strcmp(*all_files, line_in))
			all_files++;
		else
			all_lines = ft_strjoin(all_lines, ft_strjoin(line_in, "\n"));
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

/* Obtener una matriz con la cantidad de heardocs a abrir y el nombre por el que se cierran */
char	**get_files_matrix(t_shell *shell, char *holder_child)
{
	char	**all_files;
	char	*aux_line;
	int		matrix_size;
	int		elem_size;
	int		i;

	i = 0;
	matrix_size = 0;
	aux_line = holder_child;
	while (aux_line && *aux_line)
	{
		if (!ft_strncmp(aux_line, "<<", 2))
			matrix_size++;
		aux_line++;
	}
	all_files = (char **)malloc(sizeof(char *) * (matrix_size + 1));
	ft_memset(all_files, 0, matrix_size + 1);
	while (*holder_child && i <= matrix_size)
	{
		elem_size = 0;
		if (!ft_strncmp(holder_child, "<<", 2))
		{
			holder_child += 2;
			while (*holder_child && *holder_child == ' ')
				holder_child++;
			aux_line = holder_child;
			while (*aux_line && *aux_line != ' ' && *aux_line != '<')
			{
				aux_line++;
				elem_size++;
			}
			aux_line = ft_substr(holder_child, 0, elem_size);
			all_files[i] = arg_creator(shell, &aux_line);
			i++;
		}
		holder_child++;
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
