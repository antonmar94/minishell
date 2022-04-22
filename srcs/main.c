/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 21:00:57 by albzamor          #+#    #+#             */
/*   Updated: 2022/04/22 19:00:02 by albzamor         ###   ########.fr       */
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

int	main(int argc, char **argv, char** envp)
{
	(void)argv;
	t_shell *shell;


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
		//printf("PID QUE BUSCA LA LINEA [%i]\n", pid);
		shell->line = readline(BLUE"AlicornioPrompt$ "RESET);
		if (shell->line && *shell->line)
			add_history(shell->line);


		//PROBAR REDIRECCION
		redirect(shell->line); //PARA PROBAR QUE DETECTA LA REDIRECCIÖN y crea EL ARCHIVO
		//exit(0);

		
	write_history(".history_own");
	free(shell->line_walker);
	//exit (shell->exit_return);
}

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
