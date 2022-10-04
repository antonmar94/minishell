/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 18:38:39 by albzamor          #+#    #+#             */
/*   Updated: 2022/10/04 20:47:13 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_and_exit_return(t_shell *shell)
{
	printf("minishell: cd: HOME not set\n");
	shell->exit_return = 1;
}

int	search_path(t_shell *shell, char *var)
{
	char **env_aux;

	env_aux = shell->minishell_envp;
	while (*env_aux && ft_strncmp(*env_aux, var, ft_strlen(var)))
		env_aux++;
	if (!*env_aux)
		return(1);
	return (0);
}

char *get_path(t_shell *shell, char *var)
{
	char **env_aux;
	char *result;
	char **aux;

	env_aux = shell->minishell_envp;
	while (*env_aux && ft_strncmp(*env_aux, var, ft_strlen(var)))
		env_aux++;
	if (!*env_aux)
		return (NULL);
	
	aux = ft_split(*env_aux, '=');
	result = aux[1];
	return (result);
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

int	cd(t_shell *shell)
{
	int		ret;
	char	pwd[1024];

	ret = 0;
	if (shell->size_com_args == 1 || (shell->size_com_args == 2
			&& ft_strcmp(shell->command_plus_args[1], "~") == 0))
	{
		if(search_path(shell, "HOME"))
		{
			print_and_exit_return(shell);
			return(1);
		}
		else
			ret = chdir(get_path(shell, "HOME"));
	}
	else
		ret = chdir(shell->command_plus_args[1]);
	if (ret)
		ft_error(shell, shell->command_plus_args[1], 1);
	
	if (search_var_coincident(shell, "PWD"))
	{
		getcwd(pwd, sizeof(pwd));
		if (search_var_coincident(shell, "OLDPWD"))
			export_util("OLDPWD", search_var_coincident(shell, "PWD"), shell);
		else
			export_one(shell, "OLDPWD", pwd);
		export_util("PWD", pwd, shell);
	}
	
	return (0);
}
