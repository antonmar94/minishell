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

int print_pwd(void)
{
	char pwd[1024];
	;
	if(!getcwd(pwd, sizeof(pwd)))
		return (error_system_pwd());
	printf("%s>\n", pwd);
	return (0);
}

int cd(t_shell *shell)
{
	int ret = 0;

	if(shell->size_line > 2 )
		return (error_number_args());
	if(shell->size_line == 1 ||
		(shell->size_line == 2 && ft_strcmp(shell->command_plus_args[1], "~") == 0 ))
		ret = chdir(shell->path->home_user);
	else
		ret = chdir(shell->command_plus_args[1]);
	if (ret)
		return (error_wrong_path());
	//write(1, "\n", 1);
	return (0);
}

void exit_minishell(t_shell *shell)
{

	//printf("\nARGS: %s ",shell->arg_list->content);
	//printf("\n\n\n\n\nHOLAA\n");
	int number;
		
	if (!*shell->arg_list->content)
	{
		shell->exit_return = 0;
		print_header(shell, "thanks for using");
		shell->exit = 1;
	}
	if (shell->arg_list && *shell->arg_list->content)
	{
		if(shell->arg_list && shell->arg_list->next)
		{
			error_too_many_args();//No acaba
			return;
		}
		if(!ft_isdigit_str(shell->arg_list->content))
		{
			error_not_numeric();
			shell->exit_return = 255;
			shell->exit = 1;
		}
		else
		{
			number = ft_atoi(shell->arg_list->content);
			while (number < 0)
				number+=256;
			if (number >= 0 && number <= 255)
			{
				shell->exit_return = number;
				print_header(shell, "thanks for using ");
				shell->exit = 1;
			}
			if (number > 255)
			{
				number = number%256;
				shell->exit_return = number;
				print_header(shell, "thanks for using ");
				shell->exit = 1;
			} 



		}






	}
	
	





	//if *copy_arg->content
	
	/* else
	{
		printf("\n\n\n\n\nMEDIO\n");
	} */
	//shell->exit = 1;
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

	copy = shell->arg_list;
	while (copy)
	{
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
