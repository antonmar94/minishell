/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heardoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 11:33:47 by antonmar          #+#    #+#             */
/*   Updated: 2022/09/24 15:32:14 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ask_for_line(t_shell *shell, char *all_files)
{
	char	*line_in;
	char	*clean_line;

	line_in = readline("> ");
	if (check_interactive(shell, &line_in))
		return (NULL);
	if (line_in && ft_strcmp(all_files, line_in))
	{
		if (*line_in)
		{
			clean_line = line_in;
			line_in = ft_strjoin(clean_line, "\n");
			new_free(&clean_line);
		}
		else
			line_in = ft_strdup("\n");
	}
	return (line_in);
}

char	*first_line_in(t_shell *shell, char ***all_files, char **all_lines)
{
	char	*free_aux;
	char	*line_in;

	kill(shell->pipes_struct->pid, SIGUSR1);
	line_in = ask_for_line(shell, **all_files);
	if (line_in && !ft_strcmp(**all_files, line_in))
	{
		//free(line_in);
		free_aux = **all_files;
		(*all_files)++;
		free(free_aux);
	}
	else if (line_in)
	{
		free(*all_lines);
		*all_lines = ft_strdup(line_in);
	}
	return (line_in);
}

char	*next_line_in(t_shell *shell, char ***all_files, char **all_lines)
{
	char	*free_aux;
	char	*line_in;

	line_in = ask_for_line(shell, **all_files);
	if (g_interactive == 3)
		return (NULL);
	if (line_in && !ft_strcmp(**all_files, line_in))
	{
		//free(line_in);
		free_aux = **all_files;
		(*all_files)++;
		free(free_aux);
	}
	else if (line_in)
	{
		free_aux = *all_lines;
		*all_lines = ft_strjoin(*all_lines, line_in);
		free(free_aux);
	}
	return (line_in);
}

char	*get_heardoc_lines(t_shell *shell, char **all_files)
{
	char	*line_in;
	char	*all_lines;

	all_lines = NULL;
	line_in = first_line_in(shell, &all_files, &all_lines);
	if (g_interactive == 3)
	{
		errno = 1;
		return (NULL);
	}		
	while (line_in && all_files && *all_files)
	{
		free(line_in);
		line_in = next_line_in(shell, &all_files, &all_lines);
		if (g_interactive == 3)
		{
			errno = 1;
			free(all_lines);
			return (NULL);
		}
	}
	return (all_lines);
}
