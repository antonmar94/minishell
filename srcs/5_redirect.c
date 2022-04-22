/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_redirect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 20:05:39 by albzamor          #+#    #+#             */
/*   Updated: 2022/04/23 00:36:20 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void do_redirect(t_shell *shell, char **envp)
{
	int redirect_flag = 0;
	char *redirect_file = NULL;
	char *ptr = shell->line;
	int fd;

	while(*ptr != '\0')
	{
		if(*ptr == '>')
		{
			*ptr++ = '\0';
			++redirect_flag;

			if(*ptr == '>')
			{
				++redirect_flag;
				ptr++;
			}
			
			while(*ptr == ' ' && *ptr != '\0')
				ptr++;

			redirect_file = ptr;

			while(*ptr != ' ' && *ptr != '\0')
				ptr++;
				
			*ptr = '\0';
		}
		ptr++;
	}

	if(redirect_flag == 1)
	{
		fd = open(redirect_file, O_WRONLY|O_CREAT|O_TRUNC, 0664);
		dup2(fd, 1);
		execute_line(shell, envp);
	}
	else if(redirect_flag == 2)
	{
		fd = open(redirect_file, O_WRONLY|O_CREAT|O_APPEND, 0664);
		dup2(fd, 1);
		execute_line(shell, envp);
	}
	else
		execute_line(shell, envp);
}

