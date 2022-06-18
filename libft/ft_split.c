/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 14:03:46 by antonmar          #+#    #+#             */
/*   Updated: 2022/06/18 16:56:58 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	wcounter(char const *s, char c)
{
	size_t	i;
	int		wcount;

	wcount = 0;
	i = 0;
	while (i < ft_strlen(s))
	{
		if (s[i] != c && (s[i - 1] == c || i == 0))
			wcount++;
		i++;
	}
	return (wcount);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	int		j;
	int		wcount;
	char	**str;
	int		a;

	i = -1;
	j = -1;
	if (!s)
		return (0);
	wcount = wcounter(s, c);
	str = malloc(wcount * sizeof(char *) + 1);
	if (str == NULL)
		return (NULL);
	while (++j < wcount)
	{
		a = i + 1;
		while (s[++i] == c && i < ft_strlen(s))
			a++;
		while (s[i] != c && i < ft_strlen(s))
			i++;
		str[j] = ft_substr(s, a, i - a);
	}
	str[j] = 0;
	return (str);
}
