/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 20:05:39 by albzamor          #+#    #+#             */
/*   Updated: 2022/05/29 14:14:53 by elvmarti         ###   ########.fr       */
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
/* 		printf("file [%s]\n", *redirect_file);
		printf("linea [%s]\n",ptr); */
		ptr++;
	}
	return (0);
}

void	find_files(char **redirect_file, int redirect_flag)
{
	char	*ptr;
	char	*file_to_create;

	ptr = *redirect_file;
 	while (*ptr && *ptr == ' ')
		ptr++;
	file_to_create = ptr;
	redirect_flag = check_redirect(&ptr, &file_to_create);
	//*redirect_file = ptr;
/* 	while (*ptr != ' ' && *ptr != '\0')
		ptr++; */
/* 	if (ptr)
	{
		open(redirect_file, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	} */
	//*ptr = '\0';
}

void	do_redirect(t_shell *shell)
{
	int		redirect_flag;
	char	*redirect_file;
	int		fd;

	redirect_file = NULL;
	redirect_flag = check_redirect(&shell->line, &redirect_file);
	//find_files(&redirect_file, redirect_flag);
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
