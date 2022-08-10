/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09_pipes_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 11:11:52 by albzamor          #+#    #+#             */
/*   Updated: 2022/08/10 21:42:41 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execute_child_line(t_shell *shell, char **envp)
{
	split_arguments(shell);
	if (!shell->exit_return && !find_command(shell))
	{
		if (!system_commmand(shell, envp) || !shell->command)
			command_error(shell, shell->command);
	}
	exit (shell->exit_return);
}

int	execute_first(t_shell *shell, char **envp, int is_first)
{
	char	*holder_child;
	int		pid;
	t_pipes	*pipes_struct;

	pipes_struct = shell->pipes_struct;
	holder_child = create_child_line(pipes_struct);
	pipe(pipes_struct->fd1);
	pid = fork();
	pipes_struct->error = check_error_child(shell, pid);
	if (pid == 0)
	{
		new_free(&shell->line);
		shell->line = holder_child;
		pipes_first(shell, envp, is_first);
	}
	new_free(&holder_child);
	return (pid);
}

int	execute_next(t_shell *shell, char **envp, int is_first, int pid)
{
	char	*holder_child;
	t_pipes	*pipes_struct;

	pipes_struct = shell->pipes_struct;
	pipes_struct->child_counter = 0;
	if (!is_first)
		close(pipes_struct->fd2[READ_END]);
	if (*pipes_struct->holder_parent)
	{
		holder_child = create_child_line(pipes_struct);
		pipe(pipes_struct->fd2);
		pid = fork();
		pipes_struct->error = check_error_child(shell, pid);
		if (pid == 0)
			pipes_next(shell, envp, holder_child);
		else
		{
			pipes_struct->child_counter++;
			close(pipes_struct->fd2[WRITE_END]);
			if (!*pipes_struct->holder_parent || pipes_struct->error)
				close(pipes_struct->fd2[READ_END]);
		}
		new_free(&holder_child);
	}
	return (pipes_struct->child_counter);
}

int	execute_all(t_shell *shell, t_pipes *pipes_struct, char **envp)
{
	int		pid;
	int		is_first;
	int		child_number;

	pipes_struct->holder_parent = shell->line;
	pid = 0;
	child_number = 0;
	while (*(pipes_struct->holder_parent) && !pipes_struct->error)
	{
		pid = execute_first(shell, envp, is_first);
		child_number++;
		if (pid != 0)
		{
			child_number += execute_next(shell, envp, is_first, pid);
			is_first = 0;
		}
		close(pipes_struct->fd1[READ_END]);
		close(pipes_struct->fd1[WRITE_END]);
		if (pid == 0)
			exit (shell->exit_return);
	}
	return (child_number);
}

void	child_execution(t_shell *shell, char **envp)
{
	int			exit_child;
	int			child_number;

	exit_child = 0;
	child_number = 0;
	free_parent(shell);
	child_number = execute_all(shell, shell->pipes_struct, envp);
	while (child_number-- > 0)
		waitpid(-1, &exit_child, 0);
	if (WIFEXITED(exit_child))
		errno = WEXITSTATUS(exit_child);
	if (WIFSIGNALED(exit_child))
	{
		errno = WTERMSIG(exit_child);
		if (errno != 131)
			errno += 128;
	}
}
