/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 17:11:21 by antonmar          #+#    #+#             */
/*   Updated: 2022/05/07 13:18:42 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>
#include <stdio.h>

void	leaks(void)
{
	system("leaks minishell");
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

int	check_pipe_syntax(char *line)
{
	char		quotes;
	char		*checker;

	checker = line;
	while (*checker)
	{
		quotes = check_allquotes(checker);
		if (quotes)
		{
			checker++;
			while (checker && *checker != quotes)
				checker++;
		}
		if (*checker == '|')
		{
			checker++;
			if (*checker == '|')
				return (1);
			while (*checker && *checker == ' ')
			{
				if (*checker == '|')
					return (1);
				checker++;
			}
			if (!*checker)
				return (1);
		}
		checker++;
	}
	return (0);
}

void	free_shell(t_shell *shell)
{
	if(shell->aux_pointer->final_str)
		new_free(&shell->aux_pointer->final_str);

	all_clear(&shell->arg_list);
	free_and_reset_values(shell);
}

int	execute_line(t_shell *shell, char **envp)
{
	split_arguments(shell);
	if (!find_command(shell))
	{
		if (!system_commmand(shell, envp))
			command_error(shell->command);
	}

	free_shell(shell);
	return (0);
}

void	del_list(t_shell	*shell)
{
	t_arglist *copy;
	copy = shell->arg_list;
	while (copy)
	{
		if(copy->content)
		{
			free(copy->content);
			copy->content = NULL;
		}
		copy = copy->next;	
	}
	shell->arg_list = copy;
}

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
/* void eval_exit(t_shell	*shell)
{
	char *copy_line;
	shell->line_walker = shell->line;
	copy_line = shell->line;

	while (*shell->line_walker && *shell->line_walker == ' ')
		shell->line_walker++;

	add_command(shell);
	split_arguments(shell);


	if(!ft_strcmp(shell->command, "exit"))
	{
		exit_minishell(shell);
		del_list(shell);
		exit(0);
	}
		free(shell->command);
		shell->command = NULL;
		del_list(shell);
		free(shell->arg_list);
} */

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

int	check_syntax(t_shell *shell)
{
	int	error;

	error =  0;
	if (check_quotes_error(shell->line))
	{
		syntax_error();
		error = 1;
	}
	if (*pipe_next_line(shell->line))
	{
		if (check_pipe_syntax(shell->line))
		{
			syntax_error();
			error = 1;
		}
	}
	return (error);
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

int	execute_first(t_shell *shell, char **envp, int is_first)
{
	char	*holder_child;
	int		pid;
	t_pipes *pipes_struct;

	pipes_struct = shell->pipes_struct;
	holder_child = create_child_line(pipes_struct);
	pipe(pipes_struct->fd1);	
	pid = fork();
	pipes_struct->error = check_error_child(pid);
	if(pid == 0)
	{
		shell->line = holder_child;
		pipes_first(shell, envp, is_first);
	}
	return (pid);
}

int	execute_next(t_shell *shell, char **envp, int is_first, int pid)
{
	char	*holder_child;
	t_pipes *pipes_struct;

	pipes_struct = shell->pipes_struct;
	if (!is_first)
		close(pipes_struct->fd2[READ_END]);
	if (*pipes_struct->holder_parent)
	{
		holder_child = create_child_line(pipes_struct);
		pipe(pipes_struct->fd2);
		pid = fork();
		pipes_struct->error = check_error_child(pid);
		if (pid == 0)
			pipes_next(shell, envp, holder_child);
		else
		{
			close(pipes_struct->fd2[WRITE_END]);
			if (!*pipes_struct->holder_parent || pipes_struct->error)
				close(pipes_struct->fd2[READ_END]);
		}
		new_free(&holder_child);
	}
	return (pid);
}

int	execute_all(t_shell *shell, t_pipes *pipes_struct, char **envp)
{
	int		pid;
	int		is_first;

	pipes_struct->holder_parent = shell->line;
	pid = 0;
	while (*(pipes_struct->holder_parent) && !pipes_struct->error)
	{
		pid = execute_first(shell, envp, is_first);
		if (pid != 0) 
		{
			pid = execute_next(shell, envp, is_first, pid);
			is_first = 0;
		}
		close(pipes_struct->fd1[READ_END]);
		close(pipes_struct->fd1[WRITE_END]);
		if (pid == 0)
			exit (0);
	}
	return (pid);
}

int	main(int argc, char **argv, char** envp)
{
	(void)argv;
	t_shell	*shell;
	int		error;
	int		pid;
	char	*contenido;

	contenido =	NULL;
	if (argc != 1)
	{
		error_too_many_args();
		exit(0);
	}
	shell = initialice(envp);
	//wellcome_header(shell);
	read_history(".history_own");
	//fprintf(stderr, "%i", 42);
	while(!shell->exit)
	{
		error = 0;
		shell->line = readline(BLUE"AlicornioPrompt$ "RESET);
		if (shell->line && *shell->line)
			add_history(shell->line);
		error = check_syntax(shell);
		//eval_exit(shell);
		//do_redirect(shell, envp);
		pid = execute_all(shell, shell->pipes_struct, envp);
		if (pid)
			waitpid(pid, NULL, 0);
		free_shell(shell);
	}
	//easy_test_line_for_check_export(shell);//SOLO TEST ENV EXPORT LISTA
	write_history(".history_own");
	exit (shell->exit_return);
}

void	free_all(t_shell *shell)
{
	if(shell)
	{
		if (shell->path)
		{
			if(shell->path->user)
				new_free(&shell->path->user);
			if(shell->path->home_user)
				new_free(&shell->path->home_user);
			free(shell->path);
			shell->path = NULL;
		}
		if(shell->list_commands)
			free(shell->list_commands);
		if(shell->env_list)
			free_env_list(shell->env_list);
		free(shell);
		shell=NULL;
	}

}

void	free_aux_pointer(t_aux_pointer *aux_pointer)
{
	/* if((aux_pointer->first_$_found))
	{
		free(aux_pointer->first_$_found);
		aux_pointer->first_$_found = NULL;
	} */
	if(aux_pointer->new_expanded_str)
	{
		free(aux_pointer->new_expanded_str);
		aux_pointer->new_expanded_str = NULL;

	}
	/* if (aux_pointer->line_until$_joined)
	{
		free(aux_pointer->line_until$_joined);
		aux_pointer->line_until$_joined = NULL;
	} */
	/* if (aux_pointer->line_until$)
	{
		free(aux_pointer->line_until$);
		aux_pointer->line_until$ = NULL;
	} */
	free(aux_pointer);
	aux_pointer = NULL;


}

void	free_env_list(t_env_list *envp)
{

	t_env_list *copy;
	t_env_list *copy2;
	copy = envp;
	while (copy->next)
	{
		if(copy->var_name)
		{
			free(copy->var_name);
			copy->var_name = NULL;
		}
		if(copy->var_content)
		{
			free(copy->var_content);
			copy->var_content = NULL;

		}
		copy2 = copy->next;
		free(copy);
		copy = copy2;


	}
	if(copy->var_name)
	{
		free(copy->var_name);
		copy->var_name = NULL;
	}
	if(copy->var_content)
	{
		free(copy->var_content);
		copy->var_content = NULL;
	}
	free(copy);
}

void	free_and_reset_values(t_shell *shell)
{
	if(shell->line)
	{
			if(shell->line)
				free(shell->line);
			shell->line = NULL;

	}
	shell->size_line = 0;
	shell->size_args = 0;
	shell->command = NULL;
}
