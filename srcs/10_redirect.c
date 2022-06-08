/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 20:05:39 by albzamor          #+#    #+#             */
/*   Updated: 2022/06/08 21:31:11 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_redirect(char **line, char **rest_of_line, char arrow)
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
		line_size += jump_quotes(&arrow_finder) - 1;
		if (*arrow_finder == arrow)
		{
			num_arrows = 1;
			aux_finder = arrow_finder + 1;
			if (*aux_finder == arrow)
				num_arrows = 2;
			*rest_of_line = arrow_finder;
			*line = ft_substr(*line, 0, line_size);
			return (num_arrows);
		}
		line_size++;
		arrow_finder++;
	}
	return (num_arrows);
}

void	get_line_execute(char **line, char **rest_of_line, char arrow)
{
	char		*line_finder;

	while (**rest_of_line && **rest_of_line == ' ')
		(*rest_of_line)++;
		
	line_finder = *rest_of_line;
	while (*line_finder && line_finder)
	{
		jump_quotes(&line_finder);
		if (*line_finder && *line_finder == ' ')
			append_to_line(line, &line_finder, arrow);
		if (*line_finder && *line_finder == arrow)
		{
			line_finder++;
			while (*line_finder && *line_finder == ' ')
				line_finder++;
		}
		else if (*line_finder)
			line_finder++;
	}
}

int	get_line_files(t_shell *shell, char **all_files)
{
	int		num_arrows;

	num_arrows = check_redirect(&shell->line, all_files, '>');
	if (num_arrows)
	{
		get_line_execute(&shell->line, all_files, '>');
		num_arrows = get_create_files(shell, all_files, num_arrows);
		*all_files = arg_creator(shell, all_files);
		if (!*all_files || !**all_files)
		{
			error_wrong_path(shell);
			return (0);
		}
	}
	return (num_arrows);
}

int	do_redirect(t_shell *shell)
{
	int		num_arrows;
	char	*all_files;
	int		fd;

	all_files = NULL;
	num_arrows = get_line_files(shell, &all_files);
	if (num_arrows == 1 && !shell->exit_return)
	{
		fd = open(all_files, O_WRONLY | O_CREAT | O_TRUNC, 0664);
		if (fd < 0)
			error_wrong_path(shell);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (num_arrows == 2 && !shell->exit_return)
	{
		fd = open(all_files, O_WRONLY | O_CREAT | O_APPEND, 0664);
		if (fd < 0)
			error_wrong_path(shell);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (0);
}
