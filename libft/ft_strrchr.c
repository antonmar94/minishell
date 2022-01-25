/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 18:29:10 by albzamor          #+#    #+#             */
/*   Updated: 2021/06/14 13:13:30 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)

{
	int		i;
	int		flag;
	char	*s2;

	s2 = (char *)s;
	flag = -1;
	i = 0;
	while (s2[i] != '\0')
	{
		if (s2[i] == (char)c)
			flag = i;
		i++;
	}
	if ((s2[i] == '\0') && (char)c == '\0')
		flag = i;
	if (flag != -1)
		return (s2 + flag);
	else
		return (NULL);
}
