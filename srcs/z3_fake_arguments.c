/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z3_fake_arguments.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 12:24:03 by albzamor          #+#    #+#             */
/*   Updated: 2022/02/08 12:54:16 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_fake_arg_list	*fake_init_list_env(t_shell *shell, char** fake_arguments)
{
	t_fake_arg_list *init;
	t_fake_arg_list 	*this_list_var;
	int size_fake_arguments;
	int i;


	size_fake_arguments = size_matriz(fake_arguments);


	this_list_var = fake_args_list_new(fake_arguments[0]);
	fake_args_add_back(&shell->fake_arg_list, this_list_var);
	init = this_list_var;

	i = 1;
	while (++i < size_fake_arguments)
	{
		this_list_var = fake_args_list_new(fake_arguments[i]);
		fake_args_add_back(&shell->fake_arg_list, this_list_var);
	}
	return (init);


}

t_fake_arg_list	*fake_args_list_new(char* fake_content)
{
	t_fake_arg_list	*fake_arg_list;

	fake_arg_list = (t_fake_arg_list *)malloc(sizeof(t_fake_arg_list));
	if (!fake_arg_list)
		return (NULL);
	fake_arg_list->content = cut_env_var_name(fake_content);//pasar funcion para trocear var
	fake_arg_list->next = NULL;
	return (fake_arg_list );
}

void	fake_args_add_back(t_fake_arg_list **fake_arg_list, t_fake_arg_list *new)
{
	t_fake_arg_list	*aux;

	aux = *fake_arg_list;
	if (!new)
		return ;
	if (!*fake_arg_list)
	{
		*fake_arg_list = new;
		return ;
	}
	while ((*fake_arg_list)->next)
		*fake_arg_list = (*fake_arg_list)->next;
	(*fake_arg_list)->next = new;
	*fake_arg_list = aux;
}