/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z5_aux_lib.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 00:25:49 by albzamor          #+#    #+#             */
/*   Updated: 2022/02/28 13:29:36 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strjoin_whith_space(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*scopy;

	i = 0;
	j = 0;
	k = 0;
	if (!s1 || !s2)
		return (NULL);
	scopy = (void *)malloc((ft_strlen(s1) + ft_strlen(s2) + 2) * sizeof(char));
	if (!scopy)
		return (NULL);
	while (i < ft_strlen(s1))
		scopy[i++] = s1[j++];
    scopy[i++] = ' ';
	while (i < (ft_strlen(s1) + ft_strlen(s2) + 1))
		scopy[i++] = s2[k++];
	scopy[i] = '\0';
	return (scopy);
}

/* modified split to return de first str before a char */
char	*ft_split_one(char *s, char c, char d)

{
	char	*scopy;
	size_t	i;
	size_t	desplace;
	char *pp;


	i = 0;
	if (s == NULL)
		return (NULL);
	desplace = 0;
	scopy = s;
	pp = ft_substr((const char *)scopy, 0, ft_lens_2char(scopy, c, d));

	scopy = scopy + ft_desplace_2char(scopy, c, d);
	return (pp);
}

size_t	ft_desplace_2char(char const *s, char c, char d)
{
	size_t	i;
	size_t	count_word;

	count_word = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if ((s[i] != c || s[i] != d) && (s[i] == '\f' || s[i] == '\n' || s[i] == '\r'
				|| s[i] == '\t' || s[i] == '\v' || s[i] == ' '))
			i++;
		if ((s[i] != c || s[i] != d) && s[i] != '\0')
			return (i);
		while ((s[i] != c || s[i] != d) && s[i] != '\0')
		{
			i++;
		}
	}
	return (i);
}

size_t	ft_lens_2char(char *lens, char c, char d)
{
	size_t	i;

	i = 0;
	{
		while (lens[i] != '\0')
		{
			if (lens[i] == c || lens[i] == d)
				return (i);
			i++;
		}
		return (i);
	}
}
