/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_pipes_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 11:02:23 by albzamor          #+#    #+#             */
/*   Updated: 2022/05/08 12:20:06 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_error_child(int pid)
{
	int	error;

	error = 0;
	if (pid < 0)
	{
		error_child_process();
		error = 1;
	}
	return (error);
}

char	*pipe_next_line(char *line)
{
	char		quotes;

	while (*line)
	{
		quotes = check_allquotes(line);
		if (quotes)
		{
			line++;
			while (line && *line != quotes)
				line++;
		}
		if (*line == '|')
		{
			line++;
			return (line);
		}
		line++;
	}
	return (line);
}

char	*create_child_line(t_pipes *pipes_struct)
{
	char	*holder_child;
	int		i;

	holder_child = NULL;
	i = 0;
	while (pipes_struct->holder_parent[i] && pipes_struct->holder_parent[i] != '|')
				i++;
	holder_child = ft_substr(pipes_struct->holder_parent, 0, i);
	pipes_struct->holder_parent = pipe_next_line(pipes_struct->holder_parent);
	return (holder_child);
}

void	pipes_first(t_shell *shell, char **envp, int is_first)
{
	t_pipes *pipes_struct;

	pipes_struct = shell->pipes_struct;
	close(pipes_struct->fd1[READ_END]);
 	if (!is_first)
	{
		dup2(pipes_struct->fd2[READ_END], STDIN_FILENO);
		close(pipes_struct->fd2[READ_END]);
	}
	if (*pipes_struct->holder_parent)
		dup2(pipes_struct->fd1[WRITE_END], STDOUT_FILENO);
	close(pipes_struct->fd1[WRITE_END]);
	execute_line(shell, envp);
}

void	pipes_next(t_shell *shell, char **envp, char *holder_child)
{
	t_pipes *pipes_struct;

	shell->line = holder_child;
	pipes_struct = shell->pipes_struct;
	close(pipes_struct->fd1[WRITE_END]);
	close(pipes_struct->fd2[READ_END]);
	dup2(pipes_struct->fd1[READ_END], STDIN_FILENO);
	close(pipes_struct->fd1[READ_END]);
	if (*pipes_struct->holder_parent)
		dup2(pipes_struct->fd2[WRITE_END], STDOUT_FILENO);	
	close(pipes_struct->fd2[WRITE_END]);
	execute_line(shell, envp);
}
