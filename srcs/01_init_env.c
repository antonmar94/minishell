/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_init_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 18:17:21 by albzamor          #+#    #+#             */
/*   Updated: 2022/08/30 18:34:54 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env_list	*env_var_list_hidden(char *name, char *content)
{
	t_env_list	*env_list;

	env_list = (t_env_list *)malloc(sizeof(t_env_list));
	if (!env_list)
		return (NULL);
	env_list->var_name = name;
	env_list->var_content = content;
	env_list->next = NULL;
	return (env_list);
}

t_env_list	*mount_hidden_env_var(t_shell *shell, char **hidden_name,
	char **hidden_content)
{
	t_env_list	*this_list_var;
	t_env_list	*init;
	int			i;

	i = -1;
	while (++i < size_matriz(hidden_name))
	{
		this_list_var = env_var_list_hidden(hidden_name[i], hidden_content[i]);
		env_var_add_back(&shell->env_list, this_list_var);
		if (i == 0)
			init = this_list_var;
	}
	return (init);
}

t_env_list	*add_hidden_env_var(t_shell *shell)
{
	t_env_list	*init;
	char		**hidden_name;
	char		**hidden_content;

	hidden_name = malloc(sizeof(char *) * 4);
	hidden_content = malloc(sizeof(char *) * 4);
	hidden_name[0] = "0";
	hidden_name[1] = "?";
	hidden_name[2] = "~";
	hidden_name[3] = NULL;
	hidden_content[0] = "minishell";
	hidden_content[1] = "0";
	hidden_content[2] = "$~";
	hidden_content[3] = NULL;
	init = mount_hidden_env_var(shell, hidden_name, hidden_content);
	free(hidden_name);
	free(hidden_content);
	return (init);
}

t_env_list	*init_list_env(t_shell *shell, char **envp)
{
	t_env_list	*init;
	t_env_list	*this_list_var;
	int			size_envp;
	int			i;

	size_envp = size_matriz(envp);
	shell->env_list_plus = add_hidden_env_var(shell);
	this_list_var = env_var_list_new(envp[0]);
	env_var_add_back(&shell->env_list->next->next, this_list_var);
	init = this_list_var;
	i = 1;
	while (++i < size_envp)
	{
		this_list_var = env_var_list_new(envp[i]);
		env_var_add_back(&shell->env_list->next->next, this_list_var);
	}
	return (init);
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
