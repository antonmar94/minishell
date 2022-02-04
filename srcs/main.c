/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 17:11:21 by antonmar          #+#    #+#             */
/*   Updated: 2022/02/04 19:27:40 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_and_reset_values(t_shell *shell)
{
	if(shell->line)
			free(shell->line);
	shell->size_line = 0;
	shell->size_args = 0;
	shell->command = NULL;
}

int	main(int argc, char **argv, char** envp)
{
	(void)argc;
	(void)argv;
	t_shell *shell;

	//char	**list_args;

	shell = initialice(envp);
	//print_env_list(shell->env_list);

	//wellcome_header(shell);
	read_history(NULL);
	while(!shell->exit)
	{
		shell->line =readline(BLUE"AlicornioPrompt$ "RESET);
		if (shell->line && *shell->line)// sólo si exite y hay contenido
			add_history(shell->line);
		line_without_command(shell);
		//simple_quotes_argument(shell);
		//printf("%s", shell->arg_list->content);
		split_arguments(shell);
		//line_without_command(shell);  //No funciona ANTONIO
		//split_arguments(shell); NO FUNCIONA ANTONIO
		//easy_test_line_for_check_export(shell);
		//find_command(shell);
		//printf("cosas %i", count_args(shell));
		//if (arg_listing(shell) == -1)
		//	command_error();
		//print_all(shell);// imprimir argumentos y todo para comprobar;
		//list_args = shell->command_args;
		/* while (*list_args)
		{
			printf("%s\n", *list_args);
			list_args++;
		} */
		write_history(NULL);
		//all_clear(&shell->arg_list);
		free_and_reset_values(shell);
	}
	return (0);
}

/* int main()
{
	t_shell *shell;
	shell = initialice();

	wellcome_header(shell);
	read_history(NULL);// si es null coje historial ~/.history
	//add_history(line);
	//printf("MINISHELL\n");
	while(!shell->exit)
	{
		shell->line =readline(BLUE"AlicornioPrompt$ "RESET);
		//printf(RESET"el comando introucido es: %s\n"GREEN, line);
		if (shell->line && *shell->line)// sólo si exite y hay contenido
			add_history(shell->line);
		split_line_to_command(shell);

		//print_all(shell);// imprimir argumentos y todo para comprobar;

		if (*shell->line)
			find_command(shell);


		//if (ft_strcmp(shell->line, "pwd") == 0) // comparar para cada comando. Hacer una tabla con todos¿?¿?
			//printDir();

		free_and_reset_values(shell);
		write_history(NULL);
	}
	return (0);
} */
