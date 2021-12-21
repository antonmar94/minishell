/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 15:56:59 by albzamor          #+#    #+#             */
/*   Updated: 2021/06/11 13:18:37 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_len(int nbr)
{
	int	len;

	len = 0;
	if (nbr <= 0)
		++len;
	while (nbr != 0)
	{
		++len;
		nbr = nbr / 10;
	}
	return (len);
}

char	*ft_itoa(int nbr)
{
	char	*number;
	int		len;
	int		sign;

	sign = 1;
	if (nbr < 0)
		sign = -1;
	len = ft_len(nbr);
	number = malloc(sizeof(char) * (len + 1));
	if (number == NULL)
		return (NULL);
	if (nbr < 0)
		number[0] = '-';
	else if (nbr == 0)
		number[0] = '0';
	number[len] = '\0';
	while (nbr != 0)
	{
		--len;
		number[len] = sign * (nbr % 10) + '0';
		nbr = nbr / 10;
	}
	return (number);
}
