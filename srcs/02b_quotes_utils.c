/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02b_quotes_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 11:55:56 by albzamor          #+#    #+#             */
/*   Updated: 2022/06/18 17:15:48 by albzamor         ###   ########.fr       */
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
	int			size_arg;
	char		*arg_part;

	aux_arg = argument;
	size_arg = 0;
	while (*aux_arg && *aux_arg != '$')
	{
		aux_arg++;
		size_arg++;
	}
	aux_arg++;
	if (!check_allquotes(aux_arg))
		return (argument);
	arg_part = ft_substr(argument, 0, size_arg);
	new_free(&argument);
	return (ft_strjoin(arg_part, aux_arg));
}
