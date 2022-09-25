/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 11:23:09 by antonmar          #+#    #+#             */
/*   Updated: 2022/09/24 15:32:31 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	jump_quotes(char **line_to_ignore)
{
	char	quotes;
	int		size_quotes;

	size_quotes = 0;
	quotes = check_allquotes(*line_to_ignore);
	if (quotes)
	{
		(*line_to_ignore)++;
		size_quotes++;
		while (**line_to_ignore != quotes)
		{
			(*line_to_ignore)++;
			size_quotes++;
		}
		size_quotes++;
		return (size_quotes);
	}
	return (1);
}

void	append_to_line(char **line, char **line_finder, char arrow)
{
	char	*aux_append;
	int		size_append;

	aux_append = *line_finder;
	size_append = 0;
	while (*aux_append && *aux_append != arrow)
	{
		size_append += jump_quotes(&aux_append);
		aux_append++;
	}
	*line_finder = ft_substr(*line_finder, 0, size_append);
	*line = ft_strjoin(*line, *line_finder);
	*line_finder = aux_append;
}

int	redirect_resolution(t_shell *shell, t_pipes *pipes_struct)
{
	int		*fd;
	int		fd_file;

	if (pipes_struct->last_arrows == 2)
		fd = pipes_struct->fd_red;
	else
		fd = pipes_struct->fd_in;
	if (pipe(fd) < 0)
		return (-1);
	if (pipes_struct->heardoc_lines)
		ft_putstr_fd(pipes_struct->heardoc_lines, fd[WRITE_END]);
	if (*pipes_struct->simple_files)
	{
		fd_file = open(*pipes_struct->simple_files, O_RDONLY);
		if (check_file_error(shell, fd_file, *pipes_struct->simple_files))
			return (1);
		if (pipes_struct->last_arrows == 1)
			dup2(fd_file, fd[READ_END]);
		close(fd_file);
	}
	close(fd[WRITE_END]);
	dup2(fd[READ_END], STDIN_FILENO);
	close(fd[READ_END]);
	return (0);
}
