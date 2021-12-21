/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 00:18:38 by albzamor          #+#    #+#             */
/*   Updated: 2021/06/11 13:22:07 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))

{
	unsigned int	size;
	unsigned int	i;
	char			*scopy;

	if (f == NULL || s == NULL)
		return (NULL);
	size = ft_strlen (s);
	scopy = (char *)s;
	i = 0;
	scopy = (char *)malloc(sizeof(char) * (size + 1));
	if (scopy == NULL)
		return (NULL);
	while (i < size)
	{
		scopy[i] = f(i, s[i]);
		i++;
	}
	scopy[size] = '\0';
	return (scopy);
}
