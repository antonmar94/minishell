/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 11:28:01 by antonmar          #+#    #+#             */
/*   Updated: 2022/09/24 15:31:44 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*create_child_line(t_pipes *pipes_struct)
{
	char	*child_line;
	int		size;
	char	*parent_aux;

	child_line = NULL;
	parent_aux = pipes_struct->holder_parent;
	size = get_size_line(parent_aux);
	child_line = ft_substr(parent_aux, 0, size);
	pipes_struct->holder_parent = pipe_next_line(pipes_struct->holder_parent);
	return (child_line);
}

int	create_child(t_shell *shell, t_pipes *pipes_struct, int fd)
{
	free(pipes_struct->child_line);
	pipes_struct->child_line = create_child_line(pipes_struct);
	if (double_indirect(shell) < 0)
		return (-1);
	if (fd == 1)
		pipe(pipes_struct->fd1);
	else
		pipe(pipes_struct->fd2);
	pipes_struct->pid = fork();
	pipes_struct->error = check_error_child(shell, pipes_struct->pid);
	return (0);
}

int	execute_child_line(t_shell *shell, char **envp)
{
	t_pipes	*pipes_struct;

	pipes_struct = shell->pipes_struct;
	if (*pipes_struct->all_files)
	{
		if (redirect_resolution(pipes_struct) < 0)
		{
			error_wrong_path(shell, *pipes_struct->simple_files);
			exit (shell->exit_return);
		}
	}
	split_arguments(shell);
	if (!find_command(shell))
	{
		if (!system_commmand(shell, envp))
			command_error(shell, shell->command);
	}
	exit (shell->exit_return);
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
