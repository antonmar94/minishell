/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   23_list_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 20:28:58 by albzamor          #+#    #+#             */
/*   Updated: 2022/05/08 12:21:02 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

/* If found one in a list return de var content */
char *search_var_coincident(t_shell *shell, char* str_to_find)
{
	t_env_list *copy;
	copy = shell->env_list;

	while (copy->next)
	{
		if (!ft_strcmp(copy->var_name, str_to_find))
			return(copy->var_content);
		copy = copy->next;
	}
	if (!ft_strcmp(copy->var_name, str_to_find))
		return(copy->var_content);
	return(0);
}