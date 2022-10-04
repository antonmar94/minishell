/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 18:38:39 by albzamor          #+#    #+#             */
/*   Updated: 2022/10/04 18:38:54 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_and_exit_return(t_shell *shell)
{
	printf("HOME not set\n");
	shell->exit_return = 1;
}

int	cd(t_shell *shell)
{
	int		ret;
	char	pwd[1024];

	ret = 0;
	if (shell->size_com_args == 1 || (shell->size_com_args == 2
			&& ft_strcmp(shell->command_plus_args[1], "~") == 0))
	{
		if (ft_strcmp(shell->path->home_user, "Not Set") != 0)
			ret = chdir(shell->path->home_user);
		else
			print_and_exit_return(shell);
	}
	else
		ret = chdir(shell->command_plus_args[1]);
	if (ret)
		ft_error(shell, shell->command_plus_args[1], 1);
	if (search_var_coincident(shell, "PWD"))
	{
		export_util("OLDPWD", search_var_coincident(shell, "PWD"), shell);
		getcwd(pwd, sizeof(pwd));
		export_util("PWD", pwd, shell);
	}
	return (0);
}
