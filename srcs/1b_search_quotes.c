/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1b_search_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 19:13:39 by antonmar          #+#    #+#             */
/*   Updated: 2022/05/07 17:43:02 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_quotes(char *line_walker, char quotes)
{
	char	*quotes_finder;

	quotes_finder = line_walker;
	if (*quotes_finder && *quotes_finder == quotes)
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

int	check_list_flag(char *list_arg)
{
	char	*flag;

	if (!list_arg)
		return (0);
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
		if (shell->arg_list && check_list_flag(shell->arg_list->content))
		{
			shell->command_flag = "-n";
			aux_free = shell->arg_list;
			
			shell->arg_list = shell->arg_list->next;
 			free(aux_free);
			aux_free = NULL;
		}
	}
}

int	size_argument(t_shell *shell)
{
	char	*arg_sizer;
	int		size;
	int		size_quotes;
	char	quotes;

	size = 0;
	arg_sizer = shell->line_walker;
	while (*arg_sizer && *arg_sizer == ' ')
		arg_sizer++;
	while (*arg_sizer && *arg_sizer != ' ')
	{
		quotes =  check_allquotes(arg_sizer);
		size_quotes = 0;
		if (quotes)
		{
			size_quotes = size_quotes_arg(arg_sizer, quotes);
			size += size_quotes;
			arg_sizer += size_quotes;
		}
		arg_sizer++;
		size++;
	}
	return (size);
}

char	this_quote(char *line)
{
	if (*line == '\'')
		return ('\'');
	if (*line == '\"')
		return ('\"');
	return (0);
}

int	get_size_part(char	**arg_walker, char **arg_holder, char quotes)
{
	int size_part;

	size_part = 0;
	if (quotes)
	{
		size_part = size_quotes_arg(*arg_walker, quotes);
		if (**arg_walker && size_part == 0)
			(*arg_walker) += 2;
		else
		{
			(*arg_walker) += size_part + 1;
			(*arg_holder)++;
			(*arg_walker)++;
		}
	}
	else
	{
		while (**arg_walker && !this_quote(*arg_walker))
		{
			size_part++;
			(*arg_walker)++;
		}
	}
	return (size_part);
}

char	*get_arg_part(t_shell *shell, char **arg_walker, char **arg_holder)
{
	int		size_part;
	char	*arg_part;
	char	quotes;

	arg_part = NULL;
	quotes = this_quote(*arg_walker);
	size_part = get_size_part(arg_walker, arg_holder, quotes);
	if (**arg_holder && size_part > 0)
	{
 		arg_part = ft_substr(*arg_holder, 0, size_part);
		if (quotes != '\'')
			arg_part = change_dollars(shell, arg_part);
	}
	return (arg_part);
}

char	*arg_creator(t_shell *shell, char **argument)
{
	char	*arg_walker;
	char	*joined_arg;
	char	*arg_holder;
	char	*arg_part;

	joined_arg = NULL;
	arg_walker = *argument;
	arg_holder = *argument;
	while (*arg_holder)
	{
		arg_part = get_arg_part(shell, &arg_walker, &arg_holder);
		if (!joined_arg && arg_part)
			joined_arg = ft_strdup(arg_part);
		else if (arg_part)
			joined_arg = ft_strjoin(joined_arg, arg_part);
		free(arg_part);
		arg_part = NULL;
		arg_holder = arg_walker;
	}
	free(*argument);
	*argument = NULL;

	return (joined_arg);
}

int	add_arg_tolist(t_shell *shell)
{
	char		*argument;
	int			size_arg;

	size_arg = size_argument(shell);
	argument = ft_substr(shell->line_walker, 0, size_argument(shell));
	while (*shell->line_walker && (*shell->line_walker == ' ' || size_arg > 0))
	{
		shell->line_walker++;
		size_arg--;
	}
	if (argument)
	{
		argument = arg_creator(shell, &argument);
		arglstadd_back(&shell->arg_list, arg_node_new(argument));
	}
	if (!(*shell->line_walker))
		return (0);
	return (1);
}

void	create_array_args(t_shell *shell, int size)
{
	t_arglist	*holder_first;
	int			i;

	i = 0;
	holder_first = shell->arg_list;
	shell->command_plus_args = malloc(sizeof(char *) * size + 1);
	while (holder_first && shell->size_args > 0)
	{
		shell->command_plus_args[i] = holder_first->content;
		holder_first = holder_first->next;
		i++;
	}
	shell->command_plus_args[i] = NULL;
}

int	split_arguments(t_shell *shell)
{
	int			i;

	i = 1;
	shell->size_args = 0;
		shell->line_walker = shell->line;
	while (*shell->line_walker && *shell->line_walker == ' ')
		shell->line_walker++;
	if (*shell->line_walker)
		shell->size_args = 1;
	while (add_arg_tolist(shell))
		shell->size_args++;;
  	create_array_args(shell, shell->size_args);
	shell->command_args = shell->command_plus_args;
	shell->command_args++;
	if (shell->arg_list)
		add_line_command(shell);
	return (0);
}
