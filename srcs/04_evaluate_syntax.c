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

int	check_pipe_syntax(char *line)
{
	char		quotes;
	char		*checker;

	checker = line;
	while (*checker)
	{
		quotes = check_allquotes(checker);
		if (quotes)
		{
			checker++;
			while (checker && *checker != quotes)
				checker++;
		}
		if (*checker == '|')
		{
			checker++;
			if (*checker == '|')
				return (1);
			while (*checker && *checker == ' ')
			{
				if (*checker == '|')
					return (1);
				checker++;
			}
			if (!*checker)
				return (1);
		}
		checker++;
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

int	check_syntax(t_shell *shell)
{
	int	error;

	error =  0;
	if (check_quotes_error(shell->line))
	{
		syntax_error();
		error = 1;
	}
	if (*pipe_next_line(shell->line))
	{
		if (check_pipe_syntax(shell->line))
		{
			syntax_error();
			error = 1;
		}
	}
	return (error);
}