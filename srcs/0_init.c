/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 16:33:27 by antonmar          #+#    #+#             */
/*   Updated: 2022/04/20 20:12:07 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_path *init_path(t_shell *shell)
{

	shell->path->user = ft_strdup(getenv("USER"));
	shell->path->home = ft_strdup("/Users/");
	shell->path->home_user = ft_strjoin(shell->path->home, shell->path->user);
	return(shell->path);
}

t_shell *initialice(char** envp)
{
	t_shell *shell;

	shell = malloc(sizeof(t_shell));
	shell->exit = 0;
	shell->size_args = 0;
	shell->path = malloc(sizeof(t_path));
	shell->path = init_path(shell);
	shell->env_list = init_list_env(shell, envp);
	shell->aux_pointer = malloc(sizeof(t_aux_pointer));
	shell->line = NULL;
	shell->line_walker = NULL;
	shell->command_args = NULL;
	shell->final_line = NULL;
	shell->size_c = 11;//Numero de comandos actualizar al final
	shell->list_commands = malloc(sizeof(char*) * shell->size_c);
	shell->list_commands[0]="";
	shell->list_commands[1]="pwd";
	shell->list_commands[2]="hello";
	shell->list_commands[3]="help";
	shell->list_commands[4]="cd";
	shell->list_commands[5]="echo";
	shell->list_commands[6]="clear";
	shell->list_commands[7]="export";
	shell->list_commands[8]="env";// borrar?? solo para comprobar env
	shell->list_commands[9]="unset";
	shell->list_commands[10]="exit";
	// NO AÑADIR COMANDO SI AUMENTAR SIZE_C
	return (shell);
}






t_arglist	*arg_node_new(char *first_arg)
{
	t_arglist	*arg_list;

	arg_list = (t_arglist *)malloc(sizeof(t_arglist));
	if (!arg_list)
		return (NULL);
	arg_list->content = first_arg;
	arg_list->next = NULL;
	return (arg_list);
}

void	arglstadd_back(t_arglist **arg_lst, t_arglist *new)
{
	t_arglist	*aux;

	aux = *arg_lst;
	//printf(RED"startarg: %s\n"RESET, new->content);
	if (!new)
		return ;
	if (!*arg_lst)
	{
		*arg_lst = new;
		return ;
	}
	while ((*arg_lst)->next)
		*arg_lst = (*arg_lst)->next;
	(*arg_lst)->next = new;
	*arg_lst = aux;
}

void	all_clear(t_arglist **arg_lst)
{
	t_arglist *cleaner;
	t_arglist *aux;

	cleaner = *arg_lst;
	if (*arg_lst)
	{
		while (cleaner->content && cleaner->next)
		{
			aux = cleaner->next;
			free(cleaner);
			cleaner->content = NULL;
			cleaner->next = NULL;
			cleaner = aux;
		}
		cleaner->content = NULL;
		cleaner->next = NULL;
		*arg_lst = NULL;
	}
}