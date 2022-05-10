/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   al_aux_lib.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 00:25:49 by albzamor          #+#    #+#             */
/*   Updated: 2022/05/10 23:59:53 by albzamor         ###   ########.fr       */
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

size_t	ft_lens_2char_zero(char *lens, char c, char d)
{
	size_t	i;

	i = 0;
	{
		while (lens[i] != '\0')
		{
			if (lens[i] == c || lens[i] == d || lens[i] != '_')
			{
				return (i);
			}
			i++;
		}
		return (i);
	}
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
	//printf("SIZE A CORTAR [%lu]\n", ft_lens_2char(scopy, c, d));
	pp = ft_substr((const char *)scopy, 0, ft_lens_2char_zero(scopy, c, d));
	scopy = scopy + ft_desplace_2char(scopy, c, d);
	if (ft_isdigit(pp[0]) && pp[0] !='0')
		return (pp + 1);
	
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
		if ((!ft_isalpha(s[i]) || s[i] != c || s[i] != d) && (s[i] == '\f' || s[i] == '\n' || s[i] == '\r'
				|| s[i] == '\t' || s[i] == '\v' || s[i] == ' '))
			i++;
		if ((!ft_isalpha(s[i]) || s[i] != d) && s[i] != '\0')
			return (i);
		while ((!ft_isalpha(s[i]) || s[i] != c || s[i] != d) && s[i] != '\0')
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
			if ((lens[i] == c || lens[i] == d || (!ft_isalpha(lens[i]) && lens[i] != '_')) && ((lens[i] != '?') && (lens[i] != '0')))
				return (i);
			i++;
		}
		return (i);
	}
}


int	ft_isalpha_str(char *str, char c)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[i]))
		return (0);
	while (str[i] != c && str[i])
	{
		if (ft_isalnum(str[i]) || str[i] == '_')
			i++;
		else
			return (0);
	}
	return (1);
}

int	ft_isdigit_str(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			i++;
		else
			return (0);
	}
	return (1);
}
