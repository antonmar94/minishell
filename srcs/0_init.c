/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 16:33:27 by antonmar          #+#    #+#             */
/*   Updated: 2022/01/29 21:18:33 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_path *init_path(t_shell *shell)
{

	shell->path->user = ft_strdup(getenv("USER"));
	shell->path->home = ft_strdup("/Users/");
	shell->path->home_user = ft_strjoin(shell->path->home, shell->path->user);
	return(shell->path);
}


t_shell *initialice()
{
	t_shell *shell;

	shell = malloc(sizeof(t_shell));
	shell->exit = 0;
	shell->path = malloc(sizeof(t_path));
	shell->path = init_path(shell);
	shell->line = NULL;
	shell->line_walker = NULL;
	shell->line_args = NULL;
	shell->size_c = 7;//Numero de comandos actualizar al final
	shell->list_commands = malloc(sizeof(char*) * shell->size_c);
	shell->list_commands[0]="pwd";
	shell->list_commands[1]="exit";
	shell->list_commands[2]="hello";
	shell->list_commands[3]="help";
	shell->list_commands[4]="cd";
	shell->list_commands[5]="echo";
	shell->list_commands[6]="clear";
	return (shell);
}