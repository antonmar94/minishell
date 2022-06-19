/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11b_indirect_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 20:38:53 by antonmar          #+#    #+#             */
/*   Updated: 2022/06/19 19:56:08 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	in_file_size(char **aux_finder, char **files_finder, int *num_arrows)
{
	int	file_size;

	*num_arrows = 0;
	file_size = 0;
	while (**files_finder && **files_finder == '<')
	{
		(*num_arrows)++;
		(*files_finder)++;
	}
	while (**files_finder && **files_finder == ' ')
		(*files_finder)++;
	*aux_finder = *files_finder;
	while (**aux_finder && **aux_finder != ' ' && **aux_finder != '<')
	{
		file_size += jump_quotes(aux_finder);
		(*aux_finder)++;
	}
	return (file_size);
}

void	check_file(t_shell *shell, char *file_in_line, int file_size)
{	
	char	*file_name;
	char	*file_name_clean;

	file_name = ft_substr(file_in_line, 0, file_size);
	file_name_clean = arg_creator(shell, &file_name);
	if (access(file_name_clean, R_OK) < 0)
		ft_error(shell, file_name_clean, 1);
}

int	two_pre_arrows(t_shell *shell, char *all_files)
{
	char	*line_in;
	int		fd[2];

	line_in = NULL;
	if (pipe(fd) < 0)
		return (1);
	line_in = ask_for_line(shell, fd, all_files);
	while (ft_strcmp(all_files, line_in))
	{
		new_free(&line_in);
		line_in = ask_for_line(shell, fd, all_files);
	}
	new_free(&line_in);
	close(fd[WRITE_END]);
	close(fd[READ_END]);
	return (0);
}

int	open_line(t_shell *shell, char *file_in_line, int file_size)
{
	char	*file_name;
	char	*file_name_clean;

	if (!shell->exit_return)
	{
		file_name = ft_substr(file_in_line, 0, file_size);
		file_name_clean = arg_creator(shell, &file_name);
		if (two_pre_arrows(shell, file_name_clean))
			ft_error(shell, file_name_clean, errno);
	}
	return (0);
}

int	get_in_files(t_shell *shell, char **rest_of_line, int num_arrows)
{
	char	*files_finder;
	char	*aux_finder;
	int		file_size;

	files_finder = *rest_of_line;
	while (*files_finder && !shell->exit_return)
	{
		jump_quotes(&files_finder);
		if (*files_finder && *files_finder == '<')
		{
			file_size = in_file_size(&aux_finder, &files_finder, &num_arrows);
			if (check_last(&aux_finder, '<'))
			{
				*rest_of_line = ft_substr(files_finder, 0, file_size);
				return (num_arrows);
			}
			if (num_arrows == 1)
				check_file(shell, files_finder, file_size);
			else
				open_line(shell, files_finder, file_size);
		}
		files_finder++;
	}
	return (num_arrows);
}
