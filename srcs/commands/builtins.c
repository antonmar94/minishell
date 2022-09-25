/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 12:16:27 by albzamor          #+#    #+#             */
/*   Updated: 2022/09/25 03:37:14 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	print_pwd(t_shell *shell)
{
	char	pwd[1024];

	if (!getcwd(pwd, sizeof(pwd)))
		return (ft_error(shell, "", 992));
	printf("%s\n", pwd);
	return (0);
}

int	cd(t_shell *shell)
{
	int	ret;
	char	pwd[1024];

	ret = 0;
	if (shell->size_com_args == 1
		|| (shell->size_com_args == 2
			&& ft_strcmp(shell->command_plus_args[1], "~") == 0))
				{
					if (ft_strcmp(shell->path->home_user, "Not Set") != 0)
						ret = chdir(shell->path->home_user);
					else
					{
						printf("HOME not set\n");
						shell->exit_return = 1;
					}
				}
	else
		ret = chdir(shell->command_plus_args[1]);
	if (ret)
		ft_error(shell, shell->command_plus_args[1], 1);

	if (getenv("PWD"))
	{
		export_util("OLDPWD", getenv("PWD"), shell);
		getcwd(pwd, sizeof(pwd));
		export_util("PWD", pwd, shell);
	}
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

t_env_list	*env_var_list_new_char(char *var_name, char *var_content)
{
	t_env_list	*env_list;

	env_list = (t_env_list *)malloc(sizeof(t_env_list));
	if (!env_list)
		return (NULL);
	env_list->var_name = var_name;
	env_list->var_content = var_content;
	env_list->next = NULL;
	return (env_list);
}


void	help(t_shell *shell)
{
	int	i;

	i = -1;
	ft_putstr_fd(GREEN"Command's List: \n"RESET, 1);
	while (++i < shell->size_c)
	{
		write(1, shell->list_commands[i], ft_strlen(shell->list_commands[i]));
		write(1, "\n", 1);
	}
}

int	echo(t_shell *shell)
{
	t_arglist	*copy;

	copy = shell->arg_list;
	while (copy)
	{
		ft_putstr_fd(copy->content, 1);
		if (copy->next)
			write(1, " ", 1);
		copy = copy->next;
	}
	if (shell->command_flag && ft_strcmp(shell->command_flag, "-n") == 0)
		return (0);
	write(1, "\n", 1);
	errno = 0;
	shell->exit_return = 0;
	return (0);
}
