/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 17:11:21 by antonmar          #+#    #+#             */
/*   Updated: 2022/04/23 12:04:10 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	if(shell->line)
		new_free(&shell->line);
}

int	execute_line(t_shell *shell, char **envp)
{
	shell->line_walker = shell->line;
	while (*shell->line_walker && *shell->line_walker == ' ')
		shell->line_walker++;
	add_command(shell);
	//printf("VA A EJECUTAR EL COMANDO [%s]\n", shell->command);
	split_arguments(shell);
	if (!find_command(shell))
	{
		if (!system_commmand(shell, envp))
			command_error(shell->command);
	}
	free_shell(shell);
	return (0);
}

int	main(int argc, char **argv, char** envp)
{
	(void)argv;
	t_shell	*shell;
	char	*holder_parent;
	char	*holder_child;
	int		has_childs;
	int 	i;
	int		pid;
	int		error;
	int		fd1[2];
	int		is_first;
	int		fd2[2];
	//int 	status;

	i = 0;
	pid = 1;
	has_childs = 0;
	error = 0;
	if (argc != 1)
	{
		error_too_many_args();
		exit(0);
	}
	shell = initialice(envp);
	wellcome_header(shell);
	read_history(".history_own");
	while(!shell->exit)
	{
		is_first = 1;
		shell->line = readline(BLUE"AlicornioPrompt$ "RESET);
		if (shell->line && *shell->line)
			add_history(shell->line);
		if (*pipe_next_line(shell->line))
		{
			if (check_pipe_syntax(shell->line))
			{
				syntax_error();
				error = 1;
			}
			has_childs = 1;
		}
		holder_parent = shell->line;
		while (*holder_parent && !error)
		{
			while (holder_parent[i] && holder_parent[i] != '|')
				i++;
			holder_child = ft_substr(holder_parent, 0, i);
			i = 0;
			holder_parent = pipe_next_line(holder_parent);
			pipe(fd1);
			pid = fork();
			if (pid < 0)
			{
				error_child_process();
				exit (shell->exit_return);
				error = 1;
			}
			if(pid == 0)
			{
				shell->line = holder_child;
 				if (!is_first)
				{
					dup2(fd2[READ_END], STDIN_FILENO);
					close(fd2[READ_END]);
				}
				if (*holder_parent)
				{
					close(fd1[READ_END]);
					dup2(fd1[WRITE_END], STDOUT_FILENO);
					close(fd1[WRITE_END]);
				}
				execute_line(shell, envp);
			}
			else if (*holder_parent)
			{
				is_first = 0;
				while (holder_parent[i] && holder_parent[i] != '|')
					i++;
				holder_child = ft_substr(holder_parent, 0, i);
				i = 0;
				holder_parent = pipe_next_line(holder_parent);
				pipe(fd2);
				close(fd1[WRITE_END]);
				pid = fork();
				if (pid < 0)
				{
					error_child_process();
					error = 1;
				}
				if (pid == 0)
				{
					shell->line = holder_child;
					dup2(fd1[READ_END], STDIN_FILENO);
					close(fd1[READ_END]);
  					if (*holder_parent)
					{
						close(fd2[READ_END]);
						dup2(fd2[WRITE_END], STDOUT_FILENO);
						close(fd2[WRITE_END]);
					}
					execute_line(shell, envp);
				}

			}
			close(fd1[READ_END]);
			close(fd2[WRITE_END]);	
		}
		if (pid)
			waitpid(pid, NULL, 0);


			

		
		if (pid == 0)
			exit (shell->exit_return);
		has_childs = 0;
		//free_and_reset_values(shell);
		//easy_test_line_for_check_export(shell);//SOLO TEST ENV EXPORT LISTA
	}
	//Se escribe en el historial al terminar el programa y se libera line_walker
	write_history(".history_own");
	free(shell->line_walker);
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
			if(shell->path->home)
				new_free(&shell->path->home);
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
