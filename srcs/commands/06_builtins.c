/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 12:16:27 by albzamor          #+#    #+#             */
/*   Updated: 2022/08/30 18:11:48 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

	ret = 0;
	if (shell->size_com_args == 1
		|| (shell->size_com_args == 2
			&& ft_strcmp(shell->command_plus_args[1], "~") == 0))
				ret = chdir(shell->path->home_user);
	else
		ret = chdir(shell->command_plus_args[1]);
	if (ret)
		ft_error(shell, shell->command_plus_args[1], 1);
	return (0);
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
	return (0);
}
