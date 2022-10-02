/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 16:19:34 by albzamor          #+#    #+#             */
/*   Updated: 2022/10/02 22:50:49 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	export(t_shell *shell)
{
	t_env_list	*new_list_var;
	char		*var_name;
	char		*var_content;
	char		**tofree;

	if (!*shell->command_args)
	{
		env_export(shell);
		return (0);
	}
	while (*shell->command_args)
	{
		if (!check_char(*shell->command_args, '='))
			return (0);
		var_name = cut_env_var_name(*(shell->command_args));
		var_content = cut_env_var_content(*(shell->command_args));
		if (varname_found(&var_name, &var_content, shell))
			return (0);
		new_list_var = env_var_list_new(*(shell->command_args));
		env_var_add_back(&shell->env_list, new_list_var);
		tofree = shell->minishell_envp;
		shell->minishell_envp = create_env_matrix(shell);
		new_free(&var_name);
		new_free(&var_content);
		free_matrix(tofree);
		free(tofree);
		shell->command_args++;
	}
	return (0);
}

t_env_list	*init_list_env_ordered(t_shell *shell, char **envp)
{
	t_env_list	*init;
	t_env_list	*this_list_var;
	int			size_envp;
	int			i;

	size_envp = size_matriz(shell->minishell_envp);
	this_list_var = env_var_list_new(shell->minishell_envp[0]);
	env_var_add_back(&shell->env_list_ordered, this_list_var);
	init = this_list_var;
	i = 1;
	while (i < size_envp)
	{
		this_list_var = env_var_list_new(envp[i]);
		env_var_add_back(&shell->env_list_ordered, this_list_var);
		i++;
	}
	return (init);
}

void free_env_list2(t_env_list *envp)
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

int	env_export(t_shell *shell)
{
	shell->env_list_ordered = init_list_env_ordered(shell, shell->minishell_envp);
	shell->env_list_ordered  = order_env_list(shell->env_list_ordered);
	print_env_list_export(shell->env_list_ordered);
	free_env_list2(shell->env_list_ordered);
    shell->env_list_ordered = NULL;
	return (0);
}



int		export_util(char *name, char *content, t_shell *shell)
{
	t_env_list	*new_list_var;
	char		**tofree;
	char 		*var_name;
	char 		*var_content;

	var_name = ft_strdup(name);
	var_content= ft_strdup(content);
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