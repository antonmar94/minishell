/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_quotes_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 11:55:56 by albzamor          #+#    #+#             */
/*   Updated: 2022/09/24 14:53:58 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	evaluate_quotes(int size, char **arg_sizer)
{
	char	quotes;
	int		size_quotes;

	quotes = check_allquotes(*arg_sizer);
	size_quotes = 0;
	if (quotes)
	{
		size_quotes = size_quotes_arg(*arg_sizer, quotes);
		size += size_quotes + 2;
		(*arg_sizer) += size_quotes + 2;
	}
	else
	{
		(*arg_sizer)++;
		size++;
	}
	return (size);
}

int	size_argument(t_shell *shell)
{
	char	*arg_sizer;
	int		size;

	size = 0;
	arg_sizer = shell->line_walker;
	while (*arg_sizer && *arg_sizer == ' ')
		arg_sizer++;
	while (*arg_sizer && *arg_sizer != ' ')
		size = evaluate_quotes(size, &arg_sizer);
	return (size);
}

int	get_size_part(char	**arg_walker, char **arg_holder, char quotes)
{
	int	size_part;

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
	char	*returned_part;
	char	quotes;

	arg_part = NULL;
	returned_part = NULL;
	quotes = this_quote(*arg_walker);
	size_part = get_size_part(arg_walker, arg_holder, quotes);
	if (**arg_holder && size_part > 0)
	{
		arg_part = ft_substr(*arg_holder, 0, size_part);
		if (quotes != '\'')
		{
			returned_part = change_dollars(shell, arg_part);
			free(arg_part);
		}
		else
			returned_part = arg_part;
	}
	return (returned_part);
}

char	*arg_creator(t_shell *shell, char **argument)
{
	char	*arg_walker;
	char	*joined_arg;
	char	*arg_holder;
	char	*arg_part;
	char	*free_joined;

	joined_arg = NULL;
	arg_walker = *argument;
	arg_holder = *argument;
	while (*arg_holder)
	{
		arg_part = get_arg_part(shell, &arg_walker, &arg_holder);
		if (!joined_arg && arg_part)
			joined_arg = ft_strdup(arg_part);
		else if (arg_part)
		{
			free_joined = joined_arg;
			joined_arg = ft_strjoin(free_joined, arg_part);
			new_free(&free_joined);
		}
		new_free(&arg_part);
		arg_holder = arg_walker;
	}
	new_free(argument);
	return (joined_arg);
}
