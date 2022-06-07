/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11b_indirect_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 20:38:53 by antonmar          #+#    #+#             */
/*   Updated: 2022/06/07 22:53:02 by antonmar         ###   ########.fr       */
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
    //printf("file nmame clean [%s]\n", file_name_clean);
    if (access(file_name_clean, R_OK) < 0)
    {
        ft_error(shell, file_name_clean, 1);
    }
       
/* 	if (open(file_name_clean, O_WRONLY | O_CREAT | O_TRUNC, 0664) < 0)
		error_wrong_path(shell); */
}

int	get_in_files(t_shell *shell, char **rest_of_line, int num_arrows)
{
	char	*files_finder;
	char	*aux_finder;
	int		file_size;

	files_finder = *rest_of_line - 1;
	while (*files_finder++ && !shell->exit_return)
	{
       
		jump_quotes(&files_finder);
		if (*files_finder && *files_finder == '<')
		{
			file_size = in_file_size(&aux_finder, &files_finder, &num_arrows);
			while (*aux_finder && *aux_finder != '<')
			{
				jump_quotes(&aux_finder);
				aux_finder++;
			}
			if (!*aux_finder)
			{
				*rest_of_line = ft_substr(files_finder, 0, file_size);
				return (num_arrows);
			}
			check_file(shell, files_finder, file_size);
		}
	}
	return (num_arrows);
}