/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 20:05:39 by albzamor          #+#    #+#             */
/*   Updated: 2022/06/01 22:18:20 by antonmar         ###   ########.fr       */
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
	}
	return (size_quotes);
}

int	check_redirect(char **line, char **rest_of_line)
{
	char	*arrow_finder;
	char	*aux_finder;
	int		line_size;
	int		num_arrows;

	arrow_finder = *line;
	line_size = 0;
	num_arrows = 0;
	while (*arrow_finder)
	{
		if (*arrow_finder == '>')
		{
			aux_finder = arrow_finder;
			aux_finder++;
			if (*aux_finder == '>')
				num_arrows = 2;
			else
				num_arrows = 1;
			*rest_of_line = arrow_finder;
			*line = ft_substr(*line, 0, line_size);
			return (num_arrows);
		}
		line_size++;
		arrow_finder++;
	}
	return (num_arrows);
}

void	get_line_execute (char **line, char **rest_of_line)
{
	char		*line_finder;
	char		*aux_append;
	int			size_append;

	while (**rest_of_line == ' ')
		(*rest_of_line)++;
	line_finder = *rest_of_line;
	while (*line_finder && line_finder)
	{
		jump_quotes(&line_finder);
		size_append = 0;
		if (*line_finder && *line_finder == ' ')
		{
			if (*line_finder && *line_finder != '>')
			{
				aux_append = line_finder;
				while (*aux_append && *aux_append != '>')
				{
					if (check_allquotes(aux_append))
						size_append += jump_quotes(&aux_append);
					else
						size_append++;
					aux_append++;
				}
				*line = ft_strjoin(*line, ft_substr(line_finder,
							0, size_append));
				line_finder = aux_append;
			}
		}
		if(*line_finder && *line_finder == '>')
		{
			line_finder++;
			while (*line_finder && *line_finder == ' ')
				line_finder++;
		}
		else if (*line_finder)
			line_finder++;
	}
}

int		get_create_files(char **rest_of_line, int num_arrows)
{
	char	*files_finder;
	char	*aux_finder;
	int		file_size;
	
	files_finder = *rest_of_line;
	while (*files_finder)
	{
		jump_quotes(&files_finder);
		file_size = 0;
		if (*files_finder && *files_finder == '>')
		{
			while (*files_finder && (*files_finder == '>' || *files_finder == ' '))
			{
				if (*files_finder == '>')
					num_arrows++;
				files_finder++;
			}
			aux_finder = files_finder;
			while (*aux_finder && (*aux_finder != '>' && *aux_finder != ' '))
			{
				if (check_allquotes(aux_finder))
					file_size += jump_quotes(&aux_finder);
				else
					file_size++;
				aux_finder++;
			}
			while (*aux_finder && (*aux_finder != '>'))
			{
				jump_quotes(&aux_finder);
				aux_finder++;
			}
			if (!*aux_finder)
			{
				*rest_of_line = ft_substr(files_finder, 0, file_size);
				return (num_arrows);
			}
			open(ft_substr(files_finder, 0, file_size), O_WRONLY | O_CREAT | O_TRUNC, 0664);
			num_arrows = 0;
		}
		files_finder++;
	}
	return (num_arrows);
}

void	do_redirect(t_shell *shell)
{
	int		num_arrows;
	char	*all_files;
	int		fd;

	all_files = NULL;
	num_arrows = check_redirect(&shell->line, &all_files);
	if (num_arrows)
	{
		get_line_execute(&shell->line, &all_files);
		num_arrows = get_create_files(&all_files, num_arrows);
	}
	if (num_arrows == 1)
	{
		fd = open(all_files, O_WRONLY | O_CREAT | O_TRUNC, 0664);
		dup2(fd, 1);
	}
	else if (num_arrows == 2)
	{
		fd = open(all_files, O_WRONLY | O_CREAT | O_APPEND, 0664);
		dup2(fd, 1);
	}
}
