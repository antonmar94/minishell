/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 17:11:21 by antonmar          #+#    #+#             */
/*   Updated: 2022/04/08 20:58:43 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	leaks(void)
{
	system("leaks minishell");
}



int	main(int argc, char **argv, char** envp)
{
	//char *changed_dollar;
	(void)argv;
	t_shell *shell;

	//atexit(leaks);
	//signal(SIGINT, sigint_handler);
	if (argc != 1)
	{
		error_too_many_args();
		exit(0);
	}

	shell = initialice(envp);
	wellcome_header(shell);
	//print_env_list(shell->env_list);
	read_history(".history_own");//BORRAR ./history cuando guardemos mierda rara
	//print_env_list(shell->env_list);
	//wellcome_header(shell);
	//read_history(NULL);
	while(!shell->exit)
	{
		//add_command(shell);
		while (add_command(shell))
			command_error();
		split_arguments(shell);
		find_command(shell);
		//easy_test_line_for_check_export(shell);//SOLO TEST ENV EXPORT LISTA
		if(shell->aux_pointer->final_str)
			new_free(&shell->aux_pointer->final_str);
		all_clear(&shell->arg_list);
		if(shell->line)
		 	free(shell->line);
		//free_and_reset_values(shell);
	}
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
