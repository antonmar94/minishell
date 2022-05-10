/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 12:16:27 by albzamor          #+#    #+#             */
/*   Updated: 2022/01/02 12:33:40 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int print_pwd(t_shell *shell)
{
	char pwd[1024];
	;
	if(!getcwd(pwd, sizeof(pwd)))
		return (error_system_pwd(shell));
	printf("%s>\n", pwd);
	return (0);
}

int cd(t_shell *shell)
{
	int ret = 0;

	if(shell->size_line == 1 ||
		(shell->size_line == 2 && ft_strcmp(shell->command_plus_args[1], "~") == 0 ))
		ret = chdir(shell->path->home_user);
	else
		ret = chdir(shell->command_plus_args[1]);
	if (ret)
		return (error_wrong_path(shell));
	//write(1, "\n", 1);
	return (0);
}


void help(t_shell *shell)
{
	int i;

	i = -1;
	ft_putstr_fdnl(GREEN"Command's List: "RESET, 1);
	while (++i < shell->size_c)
	{
		write(1, shell->list_commands[i], ft_strlen(shell->list_commands[i]));
		write(1, "\n", 1);
	}
	ft_putstr_fd(GREEN"(Pipes are coming..)"RESET, 1);
	write(1, "\n", 1);
}

int echo(t_shell *shell)
{
	t_arglist *copy;

	//printf("\nprimer:[%s]\n", shell->arg_list->next->content);
	copy = shell->arg_list;
		
	shell->exit_return=42;
	while (copy)
	{
		/* if(ft_strcmp(copy->content, "0") == 0 )
			ft_putstr_fd("minishell", 1); */
		ft_putstr_fd(copy->content, 1);
			if (copy->next)
			write(1, " ", 1);
		copy = copy->next;
	}
	if (shell->command_flag && ft_strcmp(shell->command_flag, "-n") == 0)
		return(0);
	write(1, "\n", 1);
	return (0);
}
