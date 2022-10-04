/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 12:16:27 by albzamor          #+#    #+#             */
/*   Updated: 2022/10/04 18:40:42 by albzamor         ###   ########.fr       */
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
	shell->exit_return = 0;
	return (0);
}
