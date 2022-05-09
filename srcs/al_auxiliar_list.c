/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   al_auxiliar_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 15:52:46 by albzamor          #+#    #+#             */
/*   Updated: 2022/05/09 20:31:17 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *cut_env_var_name(char* str_whith_equal_in)
{
    char *var_name;
    char *env_var_walking;
    int i;
    env_var_walking = str_whith_equal_in;
    i=0;
    while (*env_var_walking && *env_var_walking != '=')
    {
        i++;
        env_var_walking++;
    }
    var_name=ft_substr(str_whith_equal_in, 0, i);
    return(var_name);
}

char *cut_env_var_content(char* str_whith_equal_in)
{
    char *var_content;
    char *env_var_walking;
    int start;
    int end;

    env_var_walking = str_whith_equal_in;
    start=0;
    while (*env_var_walking != '=')
    {
        start++;
        env_var_walking++;
    }
    start++;
    end = start;
    env_var_walking++;
    while (*env_var_walking)
    {
        end++;
        env_var_walking++;
    }



    var_content=ft_substr(str_whith_equal_in, start, end);
    return(var_content);
}

/* boolean to find a variable */
int look_for_var_name(t_shell *shell, char *var_name_to_find)
{
	t_env_list *copy;

	copy = shell->env_list;
	while (copy->next)
	{
		if (!ft_strcmp(copy->var_name,var_name_to_find))
			return(1);
		copy = copy->next;
	}
	if (!ft_strcmp(copy->var_name,var_name_to_find))
		return(1);
	return(0);
}

/* modify variable content if it already exists otherwise returns 1*/
int change_var_content(t_shell *shell, char *var_name_to_find,
	char *var_content_to_change)
{
	t_env_list *copy;

	copy = shell->env_list;
	while (copy->next)
	{
		if (!ft_strcmp(copy->var_name,var_name_to_find))
		{
			copy->var_content = var_content_to_change;
			return(1);
		}
		copy = copy->next;
	}
	if (!ft_strcmp(copy->var_name,var_name_to_find))
	{
		copy->var_content = var_content_to_change;
		return(1);
	}
	return(0);
}

/* modify variable content if it already exists otherwise returns 1*/
int del_var_node_coincident(t_shell *shell, char *var_name_to_find)
{
	t_env_list *copy;
	t_env_list *del_copy;

	copy = shell->env_list;
	while (copy->next)
	{
		if (!ft_strcmp(copy->next->var_name,var_name_to_find))
		{
			del_copy = copy->next;
			copy->next = copy->next->next;
			free(del_copy->var_name);
			free(del_copy->var_content);
			free(del_copy);
			return(1);
		}
		copy = copy->next;
	}
	if (!ft_strcmp(copy->next->var_name,var_name_to_find))
	{
		del_copy = copy->next;
		copy->next = copy->next->next;
		free(del_copy->var_name);
		free(del_copy->var_content);
		free(del_copy);
		return(1);
	}
	return(0);
}
