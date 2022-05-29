/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 20:05:39 by albzamor          #+#    #+#             */
/*   Updated: 2022/05/29 23:11:35 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_redirect(char **line, char **redirect_file)
{
	char	*ptr;

	ptr = *line;
	while (*ptr)
	{
		if (*ptr == '>')
		{
			*ptr++ = '\0';
			*redirect_file = ptr;
			if (*ptr == '>')
			{
				(*redirect_file)++;
				return (2);
			}
			else
				return (1);
		}
		ptr++;
	}
	return (0);
}

int	next_file(char **file_to_create)
{
	char	*ptr;
	char	*aux;

	ptr = *file_to_create;
	while (*ptr && *ptr != ' ')
		ptr++;
	*ptr++ = '\0';
	aux = ptr;
	while (*aux && *aux != '>')
		aux++;
	if (!*aux)
		return (0);
	open(*file_to_create, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	*file_to_create = ptr;
	return (1);
}

void	find_files(char **redirect_file, int redirect_flag)
{
	char	*ptr;
	char	*file_to_create;

	ptr = *redirect_file;
	file_to_create = *redirect_file;
	while (redirect_flag)
	{
		while (*ptr && (*ptr == ' ' || *ptr == '>'))
			ptr++;
		file_to_create = ptr;
		redirect_flag = next_file(&file_to_create);
		ptr = file_to_create;
	}
	*redirect_file = file_to_create;
}

void	do_redirect(t_shell *shell)
{
	int		redirect_flag;
	char	*redirect_file;
	int		fd;

	redirect_file = NULL;
	redirect_flag = check_redirect(&shell->line, &redirect_file);
	find_files(&redirect_file, redirect_flag);
	if (redirect_flag == 1)
	{
		fd = open(redirect_file, O_WRONLY | O_CREAT | O_TRUNC, 0664);
		dup2(fd, 1);
	}
	else if (redirect_flag == 2)
	{
		fd = open(redirect_file, O_WRONLY | O_CREAT | O_APPEND, 0664);
		dup2(fd, 1);
	}
}
