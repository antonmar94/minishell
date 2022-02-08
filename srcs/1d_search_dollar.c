/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1d_search_dollar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 20:28:58 by albzamor          #+#    #+#             */
/*   Updated: 2022/02/08 12:55:30 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *search_var_coincident(t_env_list*env_list, char* str_to_find)
{
	t_env_list *copy;
	copy = env_list;

	while (copy->next)
	{
		if (ft_strcmp(copy->var_name, str_to_find))
			return(env_list->var_content);
		copy = copy->next;
	}
	if (ft_strcmp(copy->var_name, str_to_find))
			return(env_list->var_content);
	return(0);

}




int	change_dollars(t_env_list*env_list, t_arglist *arg_list)
{
	t_arglist	*copy;













	// no buscar en la lista de argumentos sino modificar la linea que
	// o hay ' ' fuertes y dejar la linea preparada sustituyendo los $ por el coontenido
	// de la variable env encontrada
	/* while (arg_list->next)
	{
		while (*arg_list->content != '$')
			arg_list->content++;
		arg_list->content++;
		if(search_var_coincident(env_list, ++arg_list->content))
			ft_strjoin()
		arg_list = arg_list->next;
	}
	while (*arg_list->content != '$')
			arg_list->content++;
		arg_list->content++;
		search_var_coincident(env_list, ++arg_list->content);
	return();
 */
	return(0);
}