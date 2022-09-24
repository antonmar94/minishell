/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10a_redirect_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 11:23:09 by antonmar          #+#    #+#             */
/*   Updated: 2022/09/24 11:24:18 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	create_file(t_shell *shell, char *file_in_line, int file_size)
{	
	char	*file_name;
	char	*file_name_clean;

	file_name = ft_substr(file_in_line, 0, file_size);
	if (file_name)
		file_name_clean = arg_creator(shell, &file_name);
	if (open(file_name_clean, O_WRONLY | O_CREAT | O_TRUNC, 0664) < 0)
		error_wrong_path(shell, file_name);
}

int	redirect_resolution(t_pipes *pipes_struct)
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
		if (fd_file < 0)
			return (-1);
		if (pipes_struct->last_arrows == 1)
			dup2(fd_file, fd[READ_END]);
		close(fd_file);
	}
	close(fd[WRITE_END]);
	dup2(fd[READ_END], STDIN_FILENO);
	close(fd[READ_END]);
	return (0);
}