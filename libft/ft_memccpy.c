/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 16:35:20 by albzamor          #+#    #+#             */
/*   Updated: 2021/06/01 13:40:47 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*dst2;
	unsigned char	*src2;

	c = (unsigned char)c;
	dst2 = (unsigned char *)dst;
	src2 = (unsigned char *)src;
	if ((src2 == NULL) && (dst2 == NULL))
		return (0);
	i = 0;
	while (i < n)
	{
		dst2[i] = src2[i];
		if (src2[i] == c)
			return (dst2 + i + 1);
		i++;
	}
	return (NULL);
}
