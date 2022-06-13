/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_indirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 20:37:28 by antonmar          #+#    #+#             */
/*   Updated: 2022/06/09 20:19:07 by antonmar         ###   ########.fr       */
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
			return (0);
		if (num_arrows == 1 && access(*all_files, R_OK) < 0)
		{
			ft_error(shell, *all_files, 1);
			return (0);
		}
	}
	return (num_arrows);
}

int	two_arrows(char *all_files)
{
	char	*line_in;
	int		fd[2];

	line_in = NULL;
	if (pipe(fd) < 0)
		return (1);
	line_in = readline("> ");
	if (ft_strcmp(all_files, line_in))
	{
		ft_putstr_fd(line_in, fd[WRITE_END]);
		ft_putchar_fd('\n', fd[WRITE_END]);
	}
	while (ft_strcmp(all_files, line_in))
	{
		new_free(&line_in);
		line_in = readline("> ");
		if (ft_strcmp(all_files, line_in))
		{
			ft_putstr_fd(line_in, fd[WRITE_END]);
			ft_putchar_fd('\n', fd[WRITE_END]);
		}
	}
	new_free(&line_in);
	close(fd[WRITE_END]);
	dup2(fd[READ_END], STDIN_FILENO);
	close(fd[READ_END]);
	return (0);
}

int	do_indirect(t_shell *shell)
{
	int		num_arrows;
	char	*all_files;
	int		fd;

	all_files = NULL;
	num_arrows = indirect_files(shell, &all_files);
	if (*all_files == '>')
		return (syntax_error(shell));
	if (num_arrows == 1 && !shell->exit_return)
	{
		fd = open(all_files, O_RDONLY);
		if (fd < 0)
			error_wrong_path(shell);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (num_arrows == 2 && !shell->exit_return)
	{
		if (two_arrows(all_files))
			ft_error(shell, all_files, errno);
	}
	return (0);
}
