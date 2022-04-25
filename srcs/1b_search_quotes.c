/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1b_search_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 19:13:39 by antonmar          #+#    #+#             */
/*   Updated: 2022/04/24 12:22:58 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_quotes(char *line_walker, char quotes)
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

int	size_quotes_arg(char *line_walker, char quotes)
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

int	check_quotes_error(char	*line)
{
	char	*checker;
	char	quotes;

	checker = line;
	while (*checker)
	{
		if ((*checker == '\"' || *checker == '\''))
		{
			quotes = check_allquotes(checker);
			if (!quotes)
				return (1);
			else
			{
				checker++;
				while (*checker && *checker != quotes)
					checker++;
			}
		}
		checker++;
	}
	return (0);
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
			&& !check_allquotes(shell->line_walker))
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

char	*get_arg_parts(t_shell *shell, char *argument)
{
	int			size_arg;
	char		*arg_start;
	char		quotes;
	char		*free_argument;

	while (*shell->line_walker && *shell->line_walker != ' ')
	{
		size_arg = 0;
		quotes = jump_arg_quotes(shell);
		arg_start = shell->line_walker;
		size_arg = get_size_splitted_argpart(shell, quotes);
		arg_start = ft_substr(arg_start, 0, size_arg);
		if (check_allquotes(arg_start) != '\'')
			arg_start = change_dollars(shell, arg_start);
		if (check_allquotes(arg_start))
			arg_start = del_quotes(arg_start);
		quotes = jump_flag_quotes(arg_start);
		free_argument = argument;
		argument = ft_strjoin(argument, arg_start);
		free(arg_start);
	}
	return (argument);
}

int	check_list_flag(char *list_arg)
{
	char	*flag;

	flag = list_arg;
	if (!ft_strncmp(flag, "-n", 2))
	{
		flag += 1;
		while (*flag && *flag == 'n')
			flag++;
		if (!*flag || *flag == ' ')
			return (1);
	}
	return (0);
}

void	add_line_command(t_shell *shell)
{
	t_arglist	*aux_free;

	if (shell->arg_list)
	{
		shell->command = shell->arg_list->content;
		aux_free = shell->arg_list;
		
		shell->arg_list = shell->arg_list->next;
		
		free(aux_free);
		aux_free = NULL;
		
		while (check_list_flag(shell->arg_list->content))
		{
			printf("ESTA ENTRANDO\n");
			shell->command_flag = "-n";
			aux_free = shell->arg_list;
			
			shell->arg_list = shell->arg_list->next;
 			free(aux_free);
			aux_free = NULL;
		}
	}
}

int	argument_list_creator(t_shell *shell)
{
	char		*argument;
	char		quotes;

	quotes = jump_arg_quotes(shell);
	argument = ft_substr(shell->line_walker, 0,
			get_size_splitted_argpart(shell, quotes));
	if (check_allquotes(argument) != '\'')
		argument = change_dollars(shell, argument);
	if (check_allquotes(argument))
		argument = del_quotes(argument);
	arglstadd_back(&shell->arg_list,
		arg_node_new(get_arg_parts(shell, argument)));
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
	t_arglist	*holder_first;
	int			i;
	int aux_size;

	i = 1;
	shell->size_args = 0;
	//printf("LINE WALKER EN SPLIT ARGUMENTS [%s]\n", shell->line_walker);
	if (*shell->line_walker)
		shell->size_args = 1;
	while (argument_list_creator(shell))
		shell->size_args++;
	add_line_command(shell);
	//printf("COMANDO A EJECUTAR [%s]\n", shell->command);
	//printf("FLAG DEL COMANDO [%s]\n", shell->command_flag);
	holder_first = shell->arg_list;
	shell->command_plus_args = malloc(sizeof(char *) * shell->size_args + 2);
	shell->command_args = malloc(sizeof(char *) * shell->size_args + 1);
	shell->command_plus_args[0] = shell->command;
	holder_first = shell->arg_list;
	aux_size =shell->size_args;
	 while (shell->arg_list && shell->size_args > 0 )
	{
		printf("ARGUMENTO DE LA LISTA [%s]\n", shell->arg_list->content);
		shell->command_plus_args[i] = shell->arg_list->content;
		shell->command_args[i-1] = shell->arg_list->content;
		shell->size_args--;
		shell->arg_list = shell->arg_list->next;
		i++;
		shell->size_args = aux_size;
	}
	shell->command_plus_args[i] = NULL;
	shell->command_args[i-1] = NULL;
	i = 0;
	while (shell->command_plus_args[i])
	{
		printf("COMMAND PLUS ARGS [%s]\n", shell->command_plus_args[i]);
		i++;
	}
	printf("COMMAND PLUS ARGS [%s]\n", shell->command_plus_args[i]);
	i = 0;
	while (shell->command_args[i])
	{
		printf("COMMAND ARGS [%s]\n", shell->command_args[i]);
		i++;
	}
	printf("COMMAND ARGS [%s]\n", shell->command_args[i]);
	shell->arg_list = holder_first;
	//printf("COMANDO A EJECUTAR [%s]\n", shell->command);
	return (0);
}

char	*del_quotes(char *str_to_del_quotes)
{
	char	*no_quotes;

	if (!str_to_del_quotes)
		return (NULL);
	no_quotes = ft_substr(str_to_del_quotes, 1,
			ft_strlen(str_to_del_quotes) - 2);
	free (str_to_del_quotes);
	return (no_quotes);
}
