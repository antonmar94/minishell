/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_evaluate_syntax.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 17:11:21 by antonmar          #+#    #+#             */
/*   Updated: 2022/05/08 12:18:59 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_char(char *str, char char_tofind)
{

	while (str && *str)
	{
		if (*str && *str == char_tofind)
			return(1);
		str++;	
	}
	return (0);
}

void ignore_quotes(char **line)
{
	char		quotes;

	quotes = check_allquotes(*line);
	if (quotes)
	{
		(*line)++;
		while (**line && **line != quotes)
			(*line)++;
		if (*line)
			(*line)++;
	}
}

int	check_pipe_syntax(char *line)
{
	char		*checker;

	checker = line;
 	while (*checker)
	{
		ignore_quotes(&checker);
		if (*checker == '|')
		{
			checker++;
			while (*checker && *checker == ' ')
				checker++;
			if (!*checker || *checker == '|')
				return (1);
		}
		checker++;
	}
	return (0);
}

int	check_quotes_syntax(char *line)
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
			checker++;
			while (*checker && *checker != quotes)
				checker++;
		}
		checker++;
	}
	return (0);
}

int	check_arrow_syntax(char *line, char arrow)
{
	char		*checker;

	checker = line;
	while (*checker)
	{
		ignore_quotes(&checker);
		if (*checker == arrow)
		{
			checker++;
			if (*checker == arrow)
				checker++;
			while (*checker && *checker == ' ')
			{
				if (*checker == arrow)
					return (1);
				checker++;
			}
			if (!*checker || *checker == arrow)
				return (1);
		}
		checker++;
	}
	return (0);
}

int	check_syntax(t_shell *shell)
{
	if (check_quotes_syntax(shell->line))
	{
		syntax_error(shell);
		return (1);
	}
	if (check_arrow_syntax(shell->line, '>')
		|| check_arrow_syntax(shell->line, '<'))
	{
		syntax_error(shell);
		return (1);
	}
	if (check_pipe_syntax(shell->line))
	{
		syntax_error(shell);
		return (1);
	}
	return (0);
}