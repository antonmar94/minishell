/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_pipes_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 11:02:23 by albzamor          #+#    #+#             */
/*   Updated: 2022/09/24 13:38:00 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*pipe_next_line(char *line)
{
	char		quotes;

	while (*line)
	{
		quotes = check_allquotes(line);
		if (quotes)
		{
			line++;
			while (line && *line != quotes)
				line++;
		}
		if (*line == '|')
		{
			line++;
			return (line);
		}
		line++;
	}
	return (line);
}

int	get_size_line(char *size_walker)
{
	char	quotes;
	int		size;

	size = 0;
	while (*size_walker && *size_walker != '|')
	{
		quotes = check_allquotes(size_walker);
		if (quotes)
		{
			size_walker++;
			size++;
			while (*size_walker && *size_walker != quotes)
			{
				size_walker++;
				size++;
			}
		}
		size++;
		size_walker++;
	}
	return (size);
}
