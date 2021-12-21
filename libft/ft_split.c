/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 10:04:20 by albzamor          #+#    #+#             */
/*   Updated: 2021/08/21 11:05:05 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_wordcount(char const *s, char c)
{
	size_t	i;
	size_t	count_word;

	count_word = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i] == '\f' || s[i] == '\n' || s[i] == '\r'
				|| s[i] == '\t' || s[i] == '\v' || s[i] == ' '))
			i++;
		if (s[i] != c && s[i] != '\0')
			count_word++;
		while (s[i] == c && s[i] != '\0')
		{
			if (s[i + 1] != c && s[i + 1] != '\0')
				count_word++;
			i++;
		}
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (count_word);
}

size_t	ft_desplace(char const *s, char c)
{
	size_t	i;
	size_t	count_word;

	count_word = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i] == '\f' || s[i] == '\n' || s[i] == '\r'
				|| s[i] == '\t' || s[i] == '\v' || s[i] == ' '))
			i++;
		if (s[i] != c && s[i] != '\0')
			return (i);
		while (s[i] == c && s[i] != '\0')
		{
			i++;
		}
	}
	return (i);
}

size_t	ft_lens(char *lens, char c)
{
	size_t	i;

	i = 0;
	{
		while (lens[i] != '\0')
		{
			if (lens[i] == c)
				return (i);
			i++;
		}
		return (i);
	}
}

char	**ft_split(char const *s, char c)

{
	char	*scopy;
	char	**pp;
	size_t	i;
	size_t	words;
	size_t	desplace;

	i = 0;
	if (s == NULL)
		return (NULL);
	desplace = 0;
	words = ft_wordcount(s, c);
	scopy = (char *)s;
	pp = (char **)malloc(sizeof(char *) * (words + 1));
	if (pp == NULL)
		return (NULL);
	while (i < words)
	{
		scopy = scopy + ft_desplace(scopy, c);
		pp[i] = ft_substr((const char *)scopy, 0, ft_lens(scopy, c));
		scopy = scopy + ft_lens(scopy, c) + 1;
		i++;
	}
	pp[i] = NULL;
	return (pp);
}
