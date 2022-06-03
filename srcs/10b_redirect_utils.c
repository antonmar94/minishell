/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10b_redirect_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 20:22:58 by albzamor          #+#    #+#             */
/*   Updated: 2022/06/03 20:53:53 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	append_to_line(char **line, char **line_finder)
{
	char	*aux_append;
	int		size_append;

	aux_append = *line_finder;
	size_append = 0;
	while (*aux_append && *aux_append != '>')
	{
		size_append += jump_quotes(&aux_append);
		aux_append++;
	}
	*line_finder = ft_substr(*line_finder, 0, size_append);
	*line = ft_strjoin(*line, *line_finder);
	*line_finder = aux_append;
}

int	get_file_size(char **aux_finder, char **files_finder, int *num_arrows)
{
	int	file_size;

	*num_arrows = 0;
	file_size = 0;
	while (**files_finder && **files_finder == '>')
	{
		(*num_arrows)++;
		(*files_finder)++;
	}
	while (**files_finder && **files_finder == ' ')
		(*files_finder)++;
	*aux_finder = *files_finder;
	while (**aux_finder && **aux_finder != ' ' && **aux_finder != '>')
	{
		file_size += jump_quotes(aux_finder);
		(*aux_finder)++;
	}
	return (file_size);
}

void	create_file(t_shell *shell, char *file_in_line, int file_size)
{	
	char	*file_name;
	char	*file_name_clean;

	file_name = ft_substr(file_in_line, 0, file_size);
	file_name_clean = arg_creator(shell, &file_name);
	if (open(file_name_clean, O_WRONLY | O_CREAT | O_TRUNC, 0664) < 0)
		error_wrong_path(shell);
}

int	get_create_files(t_shell *shell, char **rest_of_line, int num_arrows)
{
	char	*files_finder;
	char	*aux_finder;
	int		file_size;

	files_finder = *rest_of_line - 1;
	while (*files_finder++)
	{
		jump_quotes(&files_finder);
		if (*files_finder && *files_finder == '>')
		{
			file_size = get_file_size(&aux_finder, &files_finder, &num_arrows);
			while (*aux_finder && *aux_finder != '>')
			{
				jump_quotes(&aux_finder);
				aux_finder++;
			}
			if (!*aux_finder)
			{
				*rest_of_line = ft_substr(files_finder, 0, file_size);
				return (num_arrows);
			}
			create_file(shell, files_finder, file_size);
		}
	}
	return (num_arrows);
}
