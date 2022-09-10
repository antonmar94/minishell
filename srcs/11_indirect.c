/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_indirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 20:37:28 by antonmar          #+#    #+#             */
/*   Updated: 2022/09/10 15:43:11 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Obtener las lineas introducidas por el usuario
	juntandolas todas en "all_lines" */
char	*two_arrows(t_shell *shell, char **all_files)
{
	char	*line_in;
	char	*all_lines;

	all_lines = NULL;
	kill(shell->pipes_struct->pid, SIGUSR1);
	//printf("PETA EN ESTA PARTE\n");
	line_in = ask_for_line(shell, *all_files);
	//printf("PETA EN ESTA PARTE\n");
 	if (line_in && !ft_strcmp(*all_files, line_in))
		all_files++;
	else if (line_in)
		all_lines = ft_strdup(line_in);
	while (line_in && all_files && *all_files)
	{
		//AQUI VA A HABER LEAKS
		new_free(&line_in);
		line_in = ask_for_line(shell, *all_files);
		if (line_in && !ft_strcmp(*all_files, line_in))
			all_files++;
		else if (line_in)
			all_lines = ft_strjoin(all_lines, line_in);
	}
	return (all_lines);
}

int	do_indirect(t_shell *shell)
{
	t_pipes	*pipes_struct;
	char	**last_file;

	pipes_struct = shell->pipes_struct;
	pipes_struct->all_files = get_files_matrix(shell, shell->line, "<");
	get_clean_line(&shell->line, "<");
	//AQUI VA A HABER LEAKS
	last_file  = pipes_struct->all_files;
	while(last_file[1])
		last_file++;
	pipes_struct->all_files = last_file;
	return (0);
}

int	double_indirect(t_shell *shell)
{
	t_pipes	*pipes_struct;

	pipes_struct = shell->pipes_struct;
	pipes_struct->all_files = get_files_matrix(shell, pipes_struct->child_line, "<<");
	get_clean_line(&pipes_struct->child_line, "<<");
	if (*pipes_struct->all_files)
		pipes_struct->heardoc_lines = two_arrows(shell, pipes_struct->all_files);
	return (0);
}
