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
        
        if (access(*all_files, R_OK) < 0)
        {
            ft_error(shell, *all_files, 1);
            return (0);
        }
	}
	return (num_arrows);
}

int	do_indirect(t_shell *shell)
{
    int     num_arrows;
    char    *all_files;
    int     fd;

    all_files = NULL;
    num_arrows = indirect_files(shell, &all_files);
    if (num_arrows == 1 && !shell->exit_return)
	{
		fd = open(all_files, O_RDONLY);
		if (fd < 0)
			error_wrong_path(shell);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	return (0);
}