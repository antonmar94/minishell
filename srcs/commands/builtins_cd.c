/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 18:38:39 by albzamor          #+#    #+#             */
/*   Updated: 2022/10/04 21:14:30 by albzamor         ###   ########.fr       */
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
	char	**env_aux;

	env_aux = shell->minishell_envp;
	while (*env_aux && ft_strncmp(*env_aux, var, ft_strlen(var)))
		env_aux++;
	if (!*env_aux)
		return (1);
	return (0);
}

char	*get_path(t_shell *shell, char *var)
{
	char	**env_aux;
	char	*result;
	char	**aux;

	env_aux = shell->minishell_envp;
	while (*env_aux && ft_strncmp(*env_aux, var, ft_strlen(var)))
		env_aux++;
	if (!*env_aux)
		return (NULL);
	aux = ft_split(*env_aux, '=');
	result = aux[1];
	return (result);
}

void	mod_old_pwd(t_shell *shell)
{
	char	pwd[1024];

	if (search_var_coincident(shell, "PWD"))
	{
		getcwd(pwd, sizeof(pwd));
		if (search_var_coincident(shell, "OLDPWD"))
			export_util("OLDPWD", search_var_coincident(shell, "PWD"), shell);
		else
			export_one(shell, "OLDPWD", pwd);
		export_util("PWD", pwd, shell);
	}
}

int	cd(t_shell *shell)
{
	int		ret;

	ret = 0;
	if (shell->size_com_args == 1 || (shell->size_com_args == 2
			&& ft_strcmp(shell->command_plus_args[1], "~") == 0))
	{
		if (search_path(shell, "HOME"))
		{
			print_and_exit_return(shell);
			return (1);
		}
		else
			ret = chdir(get_path(shell, "HOME"));
	}
	else
		ret = chdir(shell->command_plus_args[1]);
	if (ret)
		ft_error(shell, shell->command_plus_args[1], 1);
	mod_old_pwd(shell);
	return (0);
}
