/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 18:29:10 by albzamor          #+#    #+#             */
/*   Updated: 2021/06/11 15:34:16 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	l;

	k = 0;
	l = ft_strlen(dst);
	if (l < dstsize)
	{
		i = ft_strlen(src) + l;
		if (dstsize > i + 1)
			j = i + 1;
		else
			j = dstsize;
		while (k + 1 < j - l)
		{
			(dst[l + k] = src[k]);
			k++;
		}
		(dst[l + k]) = '\0';
	}
	else
		i = ft_strlen(src) + dstsize;
	return (i);
}
