/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 18:29:10 by albzamor          #+#    #+#             */
/*   Updated: 2022/06/18 16:56:09 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	int		i;

	i = -1;
	ret = malloc(len + 1);
	if (ft_strlen((char *) s) <= start)
		return (ret);
	if (ret != NULL)
	{
		while (++i < (int)len && s[i + start] != '\0')
			ret[i] = s[i + start];
		ret[len] = '\0';
	}
	return (ret);
}
