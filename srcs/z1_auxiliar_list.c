/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z1_auxiliar_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 15:52:46 by albzamor          #+#    #+#             */
/*   Updated: 2022/02/03 19:18:08 by albzamor         ###   ########.fr       */
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