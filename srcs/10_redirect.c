/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 20:05:39 by albzamor          #+#    #+#             */
/*   Updated: 2022/05/30 21:30:20 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_last_part(char	**line, char **ptr)
{
	char	*no_arrow;

	no_arrow = *ptr;
	no_arrow++;
	while (*no_arrow && *no_arrow != '>')
		no_arrow++;
	if (!*no_arrow)
	{
		no_arrow = *ptr;
		while (*no_arrow && *no_arrow != ' ')
			no_arrow++;
		if (*no_arrow == ' ')
		{
			*no_arrow++ = '\0';
			*line = ft_strjoin(*line, " ");
			*line = ft_strjoin(*line, ft_substr(no_arrow,
						0, ft_strlen(no_arrow)));
		}
	}
}

int	check_redirect(char **line, char **redirect_file)
{
	char	*ptr;

	ptr = *line;
	while (*ptr)
	{
		if (*ptr == '>')
		{
			*ptr++ = '\0';
			*redirect_file = ptr;
			if (*ptr == '>')
			{
				(*redirect_file)++;
				return (2);
			}
			else
				return (1);
		}
		ptr++;
	}
	return (0);
}

int	next_file(char **files, char **file_to_create)
{
	char	*ptr;
	int		size_file;

	ptr = *files;
	size_file = 0;
	while (*ptr && *ptr != '>')
	{
		ptr++;
		size_file++;
	}
	*file_to_create = ft_substr(*files, 0, size_file);
	if (!*ptr)
		return (0);
	open(*file_to_create, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	*files = ptr;
	return (1);
}

void	find_files(char **line, char **redirect_file, int redirect_flag)
{
	char	*ptr;
	char	*files;
	char	*file_to_create;

	ptr = *redirect_file;
	files = *redirect_file;
	file_to_create = NULL;
	while (redirect_flag)
	{		
		while (*ptr && (*ptr == ' ' || *ptr == '>'))
			ptr++;
		files = ptr;
		add_last_part(line, &files);
		redirect_flag = next_file(&files, &file_to_create);
		ptr = files;
	}
	*redirect_file = file_to_create;
}

void	do_redirect(t_shell *shell)
{
	int		redirect_flag;
	char	*redirect_file;
	int		fd;

	redirect_file = NULL;
	redirect_flag = check_redirect(&shell->line, &redirect_file);
	find_files(&shell->line, &redirect_file, redirect_flag);
	if (redirect_flag == 1)
	{
		fd = open(redirect_file, O_WRONLY | O_CREAT | O_TRUNC, 0664);
		dup2(fd, 1);
	}
	else if (redirect_flag == 2)
	{
		fd = open(redirect_file, O_WRONLY | O_CREAT | O_APPEND, 0664);
		dup2(fd, 1);
	}
}
