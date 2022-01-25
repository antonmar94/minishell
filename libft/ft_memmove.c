/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 16:35:20 by albzamor          #+#    #+#             */
/*   Updated: 2021/06/01 13:47:56 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*dst2;
	unsigned char	*src2;

	i = -1;
	dst2 = (unsigned char *)dst;
	src2 = (unsigned char *)src;
	if ((src == NULL) && (dst == NULL))
		return (NULL);
	if ((len == 0) || (dst == src))
		return (dst);
	if (dst2 > src2)
	{
		while (len > 0)
		{
			dst2[len - 1] = src2[len - 1];
			len--;
		}
	}
	else if (dst2 < src2)
	{
		while (++i < len)
			dst2[i] = src2[i];
	}
	return (dst);
}
