/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   al_aux_lib.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 00:25:49 by albzamor          #+#    #+#             */
/*   Updated: 2022/09/24 11:54:07 by antonmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_var_content(t_env_list	*del_copy)
{
	free(del_copy->var_name);
	free(del_copy->var_content);
	free(del_copy);
}

/* modify variable content if it already exists otherwise returns 1*/
int	del_var_node_coincident(t_shell *shell, char *var_name_to_find)
{
	t_env_list	*copy;
	t_env_list	*del_copy;

	copy = shell->env_list_plus;
	while (copy->next)
	{
		if (!ft_strcmp(copy->next->var_name, var_name_to_find))
		{
			del_copy = copy->next;
			copy->next = copy->next->next;
			free_var_content(del_copy);
			return (1);
		}
		copy = copy->next;
	}
	if (copy->next && !ft_strcmp(copy->next->var_name, var_name_to_find))
	{
		del_copy = copy->next;
		copy->next = copy->next->next;
		free_var_content(del_copy);
		return (1);
	}
	return (0);
}

/* modified split to return de first str before a char */
char	*ft_split_one(char *s, char c, char d)
{
	char	*scopy;
	char	*pp;

	if (s == NULL)
		return (NULL);
	scopy = s;
	pp = ft_substr((const char *)scopy, 0, ft_lens_2char(scopy, c, d));
	scopy = scopy + ft_desplace_2char(scopy, c, d);
	if (ft_isdigit(pp[0]) && pp[0] != '0' )
		return (pp + 1);
	return (pp);
}

size_t	ft_desplace_2char(char const *s, char c, char d)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		if ((!ft_isalpha(s[i]) || s[i] != c || s[i] != d) && (s[i] == '\f'
				|| s[i] == '\n' || s[i] == '\r'
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
			if ((lens[i] == c || lens[i] == d || (!ft_isalpha(lens[i])
						&& lens[i] != '_')) && ((lens[i] != '?')
					&& (lens[i] != '0') && (lens[i] != '~')))
				return (i);
			i++;
		}
		return (i);
	}
}
