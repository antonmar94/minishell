/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09_pipes_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 11:11:52 by albzamor          #+#    #+#             */
/*   Updated: 2022/09/10 15:23:21 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execute_child_line(t_shell *shell, char **envp)
{
	int	*fd;
	int fd_file;
	t_pipes	*pipes_struct;

	pipes_struct = shell->pipes_struct;
	if (pipes_struct->heardoc_lines)
		fd = pipes_struct->fd_red;
	else
		fd = pipes_struct->fd_in;
	if (pipe(fd) < 0)
		return (errno);
	if (pipes_struct->heardoc_lines)
		ft_putstr_fd(pipes_struct->heardoc_lines, fd[WRITE_END]);
	if (!pipes_struct->heardoc_lines || pipes_struct->last_arrows == 1)
	{
		fd_file = open(*pipes_struct->all_files, O_RDONLY);
		dup2(fd_file, fd[READ_END]);
		close(fd_file);
	}
	close(fd[WRITE_END]);
	dup2(fd[READ_END], STDIN_FILENO);
	close(fd[READ_END]);
	split_arguments(shell);
	if (!find_command(shell))
	{
		if (!system_commmand(shell, envp)/*  || !shell->command */)
			command_error(shell, shell->command);
	}
	exit (shell->exit_return);
}

int	execute_first(t_shell *shell, char **envp, int is_first)
{
	t_pipes	*pipes_struct;

	pipes_struct = shell->pipes_struct;
	pipes_struct->child_line= create_child_line(pipes_struct);
	double_indirect(shell);
	pipe(pipes_struct->fd1);
	pipes_struct->pid = fork();
	pipes_struct->error = check_error_child(shell, pipes_struct->pid);
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
		pipes_struct->child_line = create_child_line(pipes_struct);
		double_indirect(shell);
		pipe(pipes_struct->fd2);
		pipes_struct->pid = fork();
		pipes_struct->error = check_error_child(shell, pipes_struct->pid);
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
			is_first = 0;
		}
		close(pipes_struct->fd1[READ_END]);
		close(pipes_struct->fd1[WRITE_END]);
		if (pipes_struct->pid == 0)
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
	if (child_number < 0)
		return ;
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
