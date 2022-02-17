/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z5_aux_lib.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 00:25:49 by albzamor          #+#    #+#             */
/*   Updated: 2022/02/17 00:28:15 by albzamor         ###   ########.fr       */
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