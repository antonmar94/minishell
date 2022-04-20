/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 17:11:21 by antonmar          #+#    #+#             */
/*   Updated: 2022/04/20 20:27:58 by antonmar         ###   ########.fr       */
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
	split_arguments(shell);
	if (!find_command(shell))
	{
		if (!system_commmand(shell, envp))
			command_error(shell->command);
	}
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
	//int		fd[2];
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
	read_history(".history_own");//BORRAR ./history cuando guardemos mierda rara
	while(!shell->exit)
	{


		//Se lee la line del stdinput y se añade al historial;
		shell->line = readline(BLUE"AlicornioPrompt$ "RESET);
		if (shell->line && *shell->line)
			add_history(shell->line);


		//Se comprueba la sintaxis en los pipes;
		if (*pipe_next_line(shell->line))
		{
			if (check_pipe_syntax(shell->line))
			{
				syntax_error();
				error = 1;
			}
			has_childs = 1;
		}

		//Se inicializa hold parent que recorre la line parando en cada pipe
		holder_parent = shell->line;
		while (*holder_parent && !error)
		{
			while (holder_parent[i] && holder_parent[i] != '|')
				i++;



			//Se inicializa hold child que corta el trozo que va a ejecutar cada hijo
			holder_child = ft_substr(holder_parent, 0, i);
			printf("La linea del hijo [%s]\n", holder_child);
			pipe(fd1);
			pid = fork();
			if (pid < 0)
			{
				error_child_process();
				error = 1;
			}
			if(pid == 0)
			{
				shell->line = holder_child;
				execute_line(shell, envp);
			}
			waitpid(pid, NULL, 0);
			holder_parent = pipe_next_line(holder_parent);
		}
		
		
		//Se crean tantos hijos como comandos haya que ejecutar;

		/*if (*shell->line)
			holder_parent = shell->line;
		if (*holder_parent && has_childs && !error) //controlar donde termina y demás mierdas
		{
			while (holder_parent[i] && holder_parent[i] != '|') //parte un trozo hasta que acaba o hasta el pipe (sería el primer hijo)
				i++;
			holder_child = ft_substr(holder_parent, 0, i);
			printf("el substr del padre antes de crear el primer hijo [%s]\n", holder_child);
			holder_parent = pipe_next_line(holder_parent);
			pipe(fd);
			pid = fork();
			if (pid == 0)
			{
				close(fd[READ_END]);
				printf("Entra al hijo creado\n");
				//shell->line = holder_child; //le asigna ese trozo al line de el primer hijo creado
				printf("Acaba con los ficheros, su linea es [%s]\n", shell->line);
				has_childs = 0;
				shell->line = holder_child;
			}
			else
			{
				while (*holder_parent && has_childs)
				{
					printf("Sigue el padre con holder parent [%s]\n", holder_parent);
					while (holder_parent[i] && holder_parent[i] != '|') //parte un trozo hasta que acaba o hasta el pipe (sería el segundo hijo)
						i++;
					holder_child = ft_substr(holder_parent, 0, i);
					printf("el substr del padre antes de crear el segundo hijo [%s]\n", holder_child);
					holder_parent = pipe_next_line(holder_parent);
					pipe(fd);
					pid = fork();
					if (pid == 0)
					{
						printf("Entra al segundo hijo creado\n");
						//printf("Acaba con los ficheros del segundo hijo\n");
						shell->line = holder_child; //le asigna ese trozo al line de el primer hijo creado
						printf("Acaba con los ficheros, su linea es [%s]\n", shell->line);
						has_childs = 0;
					}
					else if (*holder_parent)
					{
						printf("Sigue el padre con holder parent [%s]\n", holder_parent);
						while (holder_parent[i] && holder_parent[i] != '|') //parte un trozo hasta que acaba o hasta el pipe (sería el segundo hijo)
							i++;
						holder_child = ft_substr(holder_parent, 0, i);
						printf("el substr del padre antes de crear el tercer hijo [%s]\n", holder_child);
						pid = fork();
						if (pid == 0)
						{
							printf("Entra al tercer hijo creado\n");
							//printf("Acaba con los ficheros del segundo hijo\n");
							shell->line = holder_child; //le asigna ese trozo al line de el primer hijo creado
							printf("Acaba con los ficheros, su linea es [%s]\n", shell->line);
							has_childs = 0;
						}
					}
					if (pid)
						holder_parent = pipe_next_line(holder_parent);
				}
			}
		}
		if (pid)
			waitpid(pid, NULL, 0);
		*/



			



		free_shell(shell);
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
