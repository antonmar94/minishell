/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 18:29:10 by albzamor          #+#    #+#             */
/*   Updated: 2021/06/14 18:14:05 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*sub_str;

	if (!s)
		return (NULL);
	if (len > (ft_strlen(s) - start))
		len = len - start;
	if (ft_strlen(s) < start)
	{
		sub_str = malloc(sizeof(char) * 1);
		if (!sub_str)
			return (NULL);
		sub_str[0] = '\0';
		return (sub_str);
	}
	if (len > ft_strlen(s) - start - 1)
		len = ft_strlen(s) - start ;
	sub_str = malloc(sizeof(char) * (len + 1));
	if (!sub_str)
		return (NULL);
	i = -1;
	while ((++i < len) && s[i + start != '\0'])
		sub_str[i] = s[start + i];
	sub_str[i] = '\0';
	return (sub_str);
}
