/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1b_search_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 19:13:39 by antonmar          #+#    #+#             */
/*   Updated: 2022/03/11 20:42:25 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_quotes(char *line_walker, char quotes) //Devuelve 1 si existen comillas abiertas y cerradas
{
	char	*quotes_finder;

	quotes_finder = line_walker;
	if (*quotes_finder == quotes)
	{
		quotes_finder++;
		while (*quotes_finder)
		{
			if (*quotes_finder == quotes)
				return (1);
			quotes_finder++;
		}
	}
	return (0);
}

int	size_quotes_arg(char *line_walker, char quotes) //Devuelve el tamaño del argumento entre comillas
{
	int		i;
	char	*quotes_finder;

	i = 0;
	quotes_finder = line_walker;
	if (check_quotes(line_walker, quotes))
	{
		quotes_finder++;
		while (*quotes_finder)
		{
			if (*quotes_finder == quotes)
				return (i);
			i++;
			quotes_finder++;
		}
	}
	return (0);
}

char	check_allquotes(char *line_walker)
{
	char	*aux;

	aux = line_walker;
	if (check_quotes(aux, '\''))
		return ('\'');
	if (check_quotes(aux, '\"'))
		return ('\"');
	return (0);
}

char	jump_quotes(t_shell *shell)
{
	int		i;
	char	quotes;

	i = 0;
	quotes = check_allquotes(shell->line_walker);
	while (*shell->line_walker && quotes)
	{
		i = size_quotes_arg(shell->line_walker, quotes);
		if (*shell->line_walker && !i)
			shell->line_walker += 2;
		else if (i)
		{
			shell->line_walker++;
			return (quotes);
		}
		quotes = check_allquotes(shell->line_walker);
	}
	return (0);
}

char	jump_flag_quotes(char *flag_line)
{
	int		i;
	char	quotes;

	i = 0;
	quotes = check_allquotes(flag_line);
	while (*flag_line && quotes)
	{
		i = size_quotes_arg(flag_line, quotes);
		if (*flag_line && !i)
			flag_line += 2;
		else if (i)
		{
			flag_line++;
			return (quotes);
		}
		quotes = check_allquotes(flag_line);
	}
	return (0);
}

int	get_size_splitted_part(t_shell *shell, char quotes)
{
	int	size_command;

	size_command = 0;
	if (quotes)
	{
		while (*shell->line_walker && *shell->line_walker != quotes)
		{
			shell->line_walker++;
			size_command++;
		}
		shell->line_walker++;
	}
	else
	{
		while (*shell->line_walker && *shell->line_walker != ' '
			&& !jump_flag_quotes(shell->line_walker))
		{
			shell->line_walker++;
			size_command++;
		}
	}
	return (size_command);
}

char	*get_command_part(t_shell *shell)
{
	int		size_command;
	char	*start_command;
	char	*command;
	char	quotes;

	command = NULL;
	quotes = jump_quotes(shell);
	start_command = shell->line_walker;
	size_command = get_size_splitted_part(shell, quotes);
	command = ft_substr(start_command, 0, size_command);
	quotes = jump_quotes(shell);
	while (*shell->line_walker && *shell->line_walker != ' ')
	{
		size_command = 0;
		start_command = shell->line_walker;
		size_command = get_size_splitted_part(shell, quotes);
		start_command = ft_substr(start_command, 0, size_command);
		quotes = jump_quotes(shell);
		command = ft_strjoin(command, start_command);
	}
	while (*shell->line_walker && *shell->line_walker != ' ')
		shell->line_walker++;
	return (command);
}

void	check_flag(t_shell *shell) //Comprueba si existe la flag -n en echo y si existe la introduce en "shell->command_flag"
{
	char	*flag;
	char	*no_flag;

	no_flag = shell->line_walker;
	while (*shell->line_walker && *shell->line_walker == ' ')
		shell->line_walker++;
	flag = get_command_part(shell);
	if (!ft_strcmp(flag, "-n"))
		shell->command_flag = flag;
	else
	{
		shell->command_flag = NULL;
		shell->line_walker = no_flag;
	}
}

int	add_command(t_shell *shell)
{
	char		*aux;
	int			i;

	i = 0;
	shell->line =readline(BLUE"AlicornioPrompt$ "RESET);
	if (shell->line && *shell->line)
		add_history(shell->line);
	shell->line_walker = shell->line;
	while (*shell->line_walker && *shell->line_walker == ' ')
		shell->line_walker++;
	aux = shell->line_walker;
	if (!jump_quotes(shell) && (!*shell->line_walker || *shell->line_walker == ' '))
		return (-1);
	shell->line_walker = aux;
	shell->command = get_command_part(shell);
	while (i < shell->size_c && ft_strcmp(shell->command, shell->list_commands[i]))
		i++;
	if (i >= shell->size_c)
		return (-1);
	if (!ft_strcmp(shell->list_commands[i], "echo"))
		check_flag(shell);
	while (*shell->line_walker && *shell->line_walker == ' ')
		shell->line_walker++;
	shell->line_args = shell->line_walker;
	return (0);
}

void	add_arg(t_shell *shell, char *start_arg, int size_prev)
{
	t_arglist	*this_arg;

	if (size_prev > 0 && *start_arg)
	{
		start_arg = ft_substr(start_arg, 0, size_prev);
		this_arg = arg_node_new(start_arg);
		arglstadd_back(&shell->arg_list, this_arg);
	}
}

int	get_size_splitted_argpart(t_shell *shell, char quotes)
{
	int	size_command;

	size_command = 0;
	if (quotes)
	{
		shell->line_walker++;
		size_command++;
		while (*shell->line_walker && *shell->line_walker != quotes)
		{
			shell->line_walker++;
			size_command++;
		}
		shell->line_walker++;
		size_command++;
	}
	else
	{
		while (*shell->line_walker && *shell->line_walker != ' '
			&& !jump_flag_quotes(shell->line_walker))
		{
			shell->line_walker++;
			size_command++;
		}
	}
	return (size_command);
}

char	jump_arg_quotes(t_shell *shell)
{
	int		i;
	char	quotes;

	i = 0;
	quotes = check_allquotes(shell->line_walker);
	while (*shell->line_walker && quotes)
	{
		i = size_quotes_arg(shell->line_walker, quotes);
		if (*shell->line_walker && !i)
			shell->line_walker += 2;
		else if (i)
			return (quotes);
		quotes = check_allquotes(shell->line_walker);
	}
	return (0);
}


int	argument_list_creator(t_shell *shell)
{
	int			size_arg;
	char		*start_arg;
	char		*argument;
	char		*dollar_argument;
	char		quotes;
	t_arglist	*this_arg;

	dollar_argument = NULL;
	quotes = jump_arg_quotes(shell);
	start_arg = shell->line_walker;
	size_arg = get_size_splitted_argpart(shell, quotes);
	argument = ft_substr(start_arg, 0,size_arg);
	if (check_allquotes(argument) != '\'')
		argument = change_dollars(shell, argument);
	if (check_allquotes(start_arg))
		argument = del_quotes(argument);
	quotes = jump_flag_quotes(shell->line_walker);
	while (*shell->line_walker && *shell->line_walker != ' ')
	{
		size_arg = 0;
		quotes = jump_arg_quotes(shell);
		start_arg = shell->line_walker;
		size_arg = get_size_splitted_argpart(shell, quotes);
		start_arg = ft_substr(start_arg, 0, size_arg);
		if (check_allquotes(start_arg) != '\'')
			start_arg = change_dollars(shell, start_arg);
		if (check_allquotes(start_arg))
			start_arg = del_quotes(start_arg);
		quotes = jump_flag_quotes(start_arg);
		argument = ft_strjoin(argument, start_arg);
	}
	this_arg = arg_node_new(argument);
	arglstadd_back(&shell->arg_list, this_arg);
	if (!(*shell->line_walker))
		return (0);
	else
	{
		shell->line_walker++;
		return (1);
	}
	shell->line_walker++;
	return (1);
}

int	split_arguments(t_shell *shell)
{
	t_arglist	*printer;
	int			i;
	i = 1;
	printer = NULL;
	shell->size_args=0;
	printf("\nline walker %s", shell->line_walker);
	if(*shell->line_walker)
		shell->size_args=1;
	printf("\n size arg1: %d\n", shell->size_args);
	while (argument_list_creator(shell))
		shell->size_args++;
	printf("\n size arg2: %d\n", shell->size_args);
	shell->command_args = malloc(sizeof(char *) * shell->size_args);
	printer = shell->arg_list;
	shell->line_walker = shell->line_args;
	printf("COMMAND %s\n", shell->command);
	while (shell->arg_list)
	{
		printf("ARGS:%s\n", shell->arg_list->content);
		//if (check_allquotes(shell->arg_list->content) != '\'')
		//	shell->arg_list->content
		//		= change_dollars(shell, shell->arg_list->content);
		if (check_allquotes(shell->arg_list->content))
			shell->arg_list->content = del_quotes(shell->arg_list->content);
		shell->command_args[i] = shell->arg_list->content;
		i++;
		shell->arg_list = shell->arg_list->next;
	}
	shell->arg_list = printer;
	return (0);
}

char	*del_quotes(char *str_to_del_quotes)
{
	if (!str_to_del_quotes)
		return (NULL);
	return (ft_substr(str_to_del_quotes, 1, ft_strlen(str_to_del_quotes) - 2));
}
