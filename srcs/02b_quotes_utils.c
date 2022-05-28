/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02b_quotes_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 11:55:56 by albzamor          #+#    #+#             */
/*   Updated: 2022/05/28 14:10:28 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	this_quote(char *line)
{
	if (*line == '\'')
		return ('\'');
	if (*line == '\"')
		return ('\"');
	return (0);
}

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

char	*find_dollar_quotes(char *argument)
{
	char		*aux_arg;
	char		quotes;
	int			size_arg;
	char		*returned_str;

	aux_arg = argument;
	size_arg = 0;
	while (*aux_arg && *aux_arg != '$')
	{
		aux_arg++;
		size_arg++;
	}
	aux_arg++;
	quotes = check_allquotes(aux_arg);
	if (!quotes)
		return (argument);
	else if (size_quotes_arg(aux_arg, quotes) != 0)
	{
		returned_str = ft_substr(argument, 0, size_arg - 1);
	}
	returned_str = ft_substr(argument, 0, size_arg);
	aux_arg += size_arg;
	returned_str = ft_strjoin(returned_str, aux_arg);
	aux_arg = argument;
	return (returned_str);
}