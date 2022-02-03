/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0b_init_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 18:17:21 by albzamor          #+#    #+#             */
/*   Updated: 2022/02/03 19:18:34 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env_list	*init_list_env(t_shell *shell, char** envp)
{
	t_env_list *init;
	t_env_list	*this_list_var;
	int size_envp;
	int i;


	size_envp = size_matriz(envp);


	this_list_var = env_var_list_new(envp[0]);
	env_var_add_back(&shell->env_list, this_list_var);
	init = this_list_var;

	i = 1;
	while (++i < size_envp)
	{
		this_list_var = env_var_list_new(envp[i]);
		env_var_add_back(&shell->env_list, this_list_var);
	}
	return (init);


}

t_env_list	*env_var_list_new(char* env_var)
{
	t_env_list	*env_list;

	env_list = (t_env_list *)malloc(sizeof(t_env_list));
	if (!env_list)
		return (NULL);
	env_list->var_name = cut_env_var_name(env_var);//pasar funcion para trocear var
	env_list->var_content = cut_env_var_content(env_var);//pasar funcion para trocear var
	env_list->next = NULL;
	return (env_list);
}

void	env_var_add_back(t_env_list **env_list, t_env_list *new)
{
	t_env_list	*aux;

	aux = *env_list;
	if (!new)
		return ;
	if (!*env_list)
	{
		*env_list = new;
		return ;
	}
	while ((*env_list)->next)
		*env_list = (*env_list)->next;
	(*env_list)->next = new;
	*env_list = aux;
}



