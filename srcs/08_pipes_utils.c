/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_pipes_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 11:02:23 by albzamor          #+#    #+#             */
/*   Updated: 2022/05/29 12:12:36 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_error_child(t_shell *shell, int pid)
{
	int	error;

	error = 0;
	if (pid < 0)
	{
		error_child_process(shell);
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

int	get_size_line(char *size_walker)
{
	char	quotes;
	int		size;

	size = 0;
	while (*size_walker && *size_walker != '|')
	{
		quotes = check_allquotes(size_walker);
		if (quotes)
		{
			size_walker++;
			size++;
			while (*size_walker && *size_walker != quotes)
			{
				size_walker++;
				size++;
			}
		}
		size++;
		size_walker++;
	}
	return (size);
}

char	*create_child_line(t_pipes *pipes_struct)
{
	char	*holder_child;
	int		size;
	char	*parent_aux;

	holder_child = NULL;
	parent_aux = pipes_struct->holder_parent;
	size = get_size_line(parent_aux);
	holder_child = ft_substr(parent_aux, 0, size);
	pipes_struct->holder_parent = pipe_next_line(pipes_struct->holder_parent);
	return (holder_child);
}

void	pipes_first(t_shell *shell, char **envp, int is_first)
{
	t_pipes	*pipes_struct;

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
	do_redirect(shell);
	execute_child_line(shell, envp);
}

void	pipes_next(t_shell *shell, char **envp, char *holder_child)
{
	t_pipes	*pipes_struct;

	shell->line = holder_child;
	pipes_struct = shell->pipes_struct;
	close(pipes_struct->fd1[WRITE_END]);
	close(pipes_struct->fd2[READ_END]);
	dup2(pipes_struct->fd1[READ_END], STDIN_FILENO);
	close(pipes_struct->fd1[READ_END]);
	if (*pipes_struct->holder_parent)
		dup2(pipes_struct->fd2[WRITE_END], STDOUT_FILENO);	
	close(pipes_struct->fd2[WRITE_END]);
	do_redirect(shell);
	execute_child_line(shell, envp);
}
