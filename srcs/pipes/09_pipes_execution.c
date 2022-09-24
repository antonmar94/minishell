/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09_pipes_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 11:11:52 by albzamor          #+#    #+#             */
/*   Updated: 2022/09/24 11:32:46 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	simple_indirect(shell);
	if (!shell->exit_return)
		do_redirect(shell);
	execute_child_line(shell, envp);
}

void	pipes_next(t_shell *shell, char **envp, char *child_line)
{
	t_pipes	*pipes_struct;

	shell->line = child_line;
	pipes_struct = shell->pipes_struct;
	close(pipes_struct->fd1[WRITE_END]);
	close(pipes_struct->fd2[READ_END]);
	dup2(pipes_struct->fd1[READ_END], STDIN_FILENO);
	close(pipes_struct->fd1[READ_END]);
	if (*pipes_struct->holder_parent)
		dup2(pipes_struct->fd2[WRITE_END], STDOUT_FILENO);
	close(pipes_struct->fd2[WRITE_END]);
	simple_indirect(shell);
	if (!shell->exit_return)
		do_redirect(shell);
	execute_child_line(shell, envp);
}

int	execute_first(t_shell *shell, char **envp, int is_first)
{
	t_pipes	*pipes_struct;

	pipes_struct = shell->pipes_struct;
	if (create_child(shell, pipes_struct, 1) < 0)
		return (-1);
	if (pipes_struct->pid == 0)
	{
		shell->line = pipes_struct->child_line;
		pipes_first(shell, envp, is_first);
	}
	new_free(&pipes_struct->child_line);
	return (pipes_struct->pid);
}

int	execute_next(t_shell *shell, char **envp, int is_first)
{
	t_pipes	*pipes_struct;

	pipes_struct = shell->pipes_struct;
	pipes_struct->child_counter = 0;
	if (!is_first)
		close(pipes_struct->fd2[READ_END]);
	if (*pipes_struct->holder_parent)
	{
		if (create_child(shell, pipes_struct, 2) < 0)
			return (-1);
		if (pipes_struct->pid == 0)
			pipes_next(shell, envp, pipes_struct->child_line);
		else
		{
			pipes_struct->child_counter++;
			close(pipes_struct->fd2[WRITE_END]);
			if (!*pipes_struct->holder_parent || pipes_struct->error)
				close(pipes_struct->fd2[READ_END]);
		}
		new_free(&pipes_struct->child_line);
	}
	return (pipes_struct->child_counter);
}

int	execute_all(t_shell *shell, t_pipes *pipes_struct, char **envp)
{
	int		is_first;
	int		child_number;

	pipes_struct->holder_parent = shell->line;
	pipes_struct->pid = 0;
	child_number = 0;
	while (*(pipes_struct->holder_parent) && !pipes_struct->error)
	{
		pipes_struct->pid = execute_first(shell, envp, is_first);
		if (pipes_struct->pid < 0)
			return (-1);
		child_number++;
		if (pipes_struct->pid != 0)
		{
			child_number += execute_next(shell, envp, is_first);
			if (child_number < 0)
				return (-1);
			is_first = 0;
		}
		close(pipes_struct->fd1[READ_END]);
		close(pipes_struct->fd1[WRITE_END]);
		if (pipes_struct->pid == 0)
			exit (shell->exit_return);
	}
	return (child_number);
}


