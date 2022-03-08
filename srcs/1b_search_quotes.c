/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1b_search_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 19:13:39 by antonmar          #+#    #+#             */
/*   Updated: 2022/03/08 20:15:45 by antonmar         ###   ########.fr       */
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

int	add_command(t_shell *shell) // arreglar este método, no funciona con 'echo' hola
{
	char	*command;
	int		i;

	i = 0;
	shell->line_walker = shell->line;
	while (*shell->line_walker && *shell->line_walker == ' ')
		shell->line_walker++;
	command = get_command_part(shell);
	while (i < shell->size_c && ft_strcmp(command, shell->list_commands[i]))
		i++;
	if (i >= shell->size_c)
		return (-1);
	if (!ft_strcmp(shell->list_commands[i], "echo"))
		check_flag(shell);
	while (*shell->line_walker && *shell->line_walker == ' ')
		shell->line_walker++;
	shell->line_args = shell->line_walker;
	shell->command = shell->list_commands[i];
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

int	add_quotes_argument(t_shell *shell, char *start_arg, int size_prev)
{
	int			i;
	t_arglist	*this_arg;
	char		quotes;

	i = 0;
	quotes = check_allquotes(shell->line_walker);
	if (check_quotes(shell->line_walker, quotes))
	{
		add_arg(shell, start_arg, size_prev);
		i = size_quotes_arg(shell->line_walker, quotes) + 2;
		start_arg = shell->line_walker;
		start_arg = ft_substr(start_arg, 0, i);
		if (*start_arg)
		{
			this_arg = arg_node_new(start_arg);
			if (ft_strcmp(start_arg, "\'\'") && ft_strcmp(start_arg, "\"\""))
				arglstadd_back(&shell->arg_list, this_arg);
			shell->line_walker += i;
		}
		return (1);
	}
	return (0);
}

int	add_space_argument(t_shell *shell, char *start_arg, int size_prev)
{
	if (*shell->line_walker == ' ')
	{
		add_arg(shell, start_arg, size_prev);
		shell->line_walker++;
		return (1);
	}
	return (0);
}

int	argument_list_creator(t_shell *shell)
{
	int		size_prev;
	char	*start_arg;

	size_prev = 0;
	start_arg = shell->line_walker;
	while (*(shell->line_walker))
	{
		if (add_quotes_argument(shell, start_arg, size_prev)
			|| add_space_argument(shell, start_arg, size_prev))
		{
			if (!(*(shell->line_walker)))
				return (0);
			return (1);
		}
		shell->line_walker++;
		size_prev++;
	}
	if (!(*(shell->line_walker))) //Añade el ultimo argumento a la lista y devuelve 0 para que pare el bucle que llama a esta funcion
	{
		add_arg(shell, start_arg, size_prev);
		return (0);
	}
	shell->line_walker++;
	return (1);
}

int	split_arguments(t_shell *shell)
{
	t_arglist	*printer;
	int			i;

	i = 0;
	shell->size_args = 1;
	printer = NULL;
	while (argument_list_creator(shell))
		shell->size_args++;
	shell->command_args = malloc(sizeof(char *) * shell->size_args);
	printer = shell->arg_list;
	shell->line_walker = shell->line_args;
	while (shell->arg_list)
	{
		printf("ARGS: %s\n", shell->arg_list->content);
		if (check_allquotes(shell->arg_list->content) != '\'')
			shell->arg_list->content
				= change_dollars(shell, shell->arg_list->content);
		if (check_allquotes(shell->arg_list->content))
			shell->arg_list->content = del_quotes(shell->arg_list->content);
		shell->command_args[i] = shell->arg_list->content;
		i++;
		shell->arg_list = shell->arg_list->next;
	}
	return (0);
}

char	*del_quotes(char *str_to_del_quotes)
{
	if (!str_to_del_quotes)
		return (NULL);
	return (ft_substr(str_to_del_quotes, 1, ft_strlen(str_to_del_quotes) - 2));
}
