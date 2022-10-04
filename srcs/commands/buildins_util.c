/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 18:38:39 by albzamor          #+#    #+#             */
/*   Updated: 2022/10/04 21:10:39 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	export_util(char *name, char *content, t_shell *shell)
{
	t_env_list	*new_list_var;
	char		**tofree;
	char		*var_name;
	char		*var_content;

	var_name = ft_strdup(name);
	var_content = ft_strdup(content);
	if (varname_found(&var_name, &var_content, shell))
		return (0);
	new_list_var = env_var_list_new_char(var_name, var_content);
	env_var_add_back(&shell->env_list, new_list_var);
	tofree = shell->minishell_envp;
	shell->minishell_envp = create_env_matrix(shell);
	new_free(&var_name);
	new_free(&var_content);
	free_matrix(tofree);
	free(tofree);
	return (0);
}

int	export_one(t_shell *shell, char *var_name, char *var_content)
{
	t_env_list	*env_list;
	char		**tofree;

	env_list = (t_env_list *)malloc(sizeof(t_env_list));
	env_list->var_name = var_name;
	env_list->var_content = ft_strdup(var_content);
	env_list->next = NULL;
	env_var_add_back(&shell->env_list, env_list);
	tofree = shell->minishell_envp;
	shell->minishell_envp = create_env_matrix(shell);
	free_matrix(tofree);
	free(tofree);
	return (0);
}

void	free_env_list2(t_env_list *envp)
{
	t_env_list	*copy;
	t_env_list	*aux;

	copy = envp;
	while (copy->next)
	{
		aux = copy;
		copy = copy->next;
		free(aux->var_name);
		free(aux->var_content);
		free(aux);
	}
	free(copy->var_name);
	free(copy->var_content);
	free(copy);
}
