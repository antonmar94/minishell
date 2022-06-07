/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_indirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 20:37:28 by antonmar          #+#    #+#             */
/*   Updated: 2022/06/07 22:53:22 by antonmar         ###   ########.fr       */
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
        //printf("ENTRA AQUI [%s]\n", *all_files);
        if (access(*all_files, R_OK) < 0)
        {
            ft_error(shell, *all_files, 1);
        }
		*all_files = arg_creator(shell, all_files);
		if (!*all_files || !**all_files)
		{
			error_wrong_path(shell);
			return (0);
		}
	}
	return (num_arrows);
}

int	do_indirect(t_shell *shell)
{
    int     num_arrows;
    char    *all_files;

    all_files = NULL;
    num_arrows = indirect_files(shell, &all_files);
    if (num_arrows == 1)
    {
        get_line_execute(&shell->line, &all_files, '<');
      /*   printf("linea [%s]\n", shell->line);
        printf("all files [%s]\n", all_files); */
    }
	return (0);
}