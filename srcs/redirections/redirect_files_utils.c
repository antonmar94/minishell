/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_files_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 20:22:58 by albzamor          #+#    #+#             */
/*   Updated: 2022/10/04 19:17:27 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_file_error(t_shell *shell, int fd, char *all_files)
{
	if (fd < 0)
	{
		if (errno == EACCES)
			error_permission(shell, all_files);
		else
			error_wrong_path(shell, all_files);
		return (1);
	}
	return (0);
}

int	create_file(t_shell *shell, char *file_in_line, int file_size)
{	
	char	*file_name;
	char	*file_name_clean;
	int		fd;

	file_name = ft_substr(file_in_line, 0, file_size);
	if (file_name)
		file_name_clean = arg_creator(shell, &file_name);
	fd = open(file_name_clean, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (check_file_error(shell, fd, file_name))
		return (1);
	return (0);
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

int	get_create_files(t_shell *shell, char **rest_of_line, int num_arrows)
{
	char	*files_finder;
	char	*aux_finder;
	int		file_size;

	files_finder = *rest_of_line;
	while (*files_finder && !shell->exit_return)
	{
		jump_quotes(&files_finder);
		if (*files_finder && *files_finder == '>')
		{
			file_size = get_file_size(&aux_finder, &files_finder, &num_arrows);
			if (check_last(&aux_finder, '>'))
			{
				*rest_of_line = ft_substr(files_finder, 0, file_size);
				return (num_arrows);
			}
			if (create_file(shell, files_finder, file_size))
				return (-1);
		}
		files_finder++;
	}
	return (num_arrows);
}
