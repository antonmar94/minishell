/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1d_search_dollar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 20:28:58 by albzamor          #+#    #+#             */
/*   Updated: 2022/04/11 10:56:58 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* if found one return de var content */
char *search_var_coincident(t_shell *shell, char* str_to_find)
{
	t_env_list *copy;
	copy = shell->env_list;

	while (copy->next)
	{
		if (!ft_strcmp(copy->var_name, str_to_find))
			return(copy->var_content);
		copy = copy->next;
	}
	if (!ft_strcmp(copy->var_name, str_to_find))
		return(copy->var_content);
	return(0);
}

/**
 replace global var($) to his content
 @param line_until$ substring (malloc) filled with the chars advanceds count_until$
 @param new_expanded_str save the last piece of the string
 @param line_until$_joined
 @param content Comtent of the global var
 @param origin_line_arg the string to advance to obtain line_until$

*/
void replace_content_runaway(t_aux_pointer *pointer)
{
	pointer->line_until$ = ft_substr(pointer->origin_line_arg, 0, pointer->count_until$);
	//si anteriormente ya hay algo se concatena a lo anterior
	if(pointer->new_expanded_str)
	{
		pointer->line_until$_joined = ft_strjoin(pointer->new_expanded_str, pointer->line_until$);
		new_free(&pointer->new_expanded_str);
	}
	else
		pointer->line_until$_joined = ft_strdup(pointer->line_until$);
	pointer->new_expanded_str =ft_strjoin(pointer->line_until$_joined, pointer->content);
	pointer->origin_line_arg = pointer->origin_line_arg + pointer->count_until$ + pointer->size_arg + 1;
	pointer->count_until$ = 0;

	pointer->shell_line_walker+=pointer->size_arg;
	if(pointer->new_expanded_str)
		free(pointer->new_expanded_str);
	pointer->new_expanded_str = ft_strjoin(pointer->line_until$_joined, pointer->content);

}

/**
 replace global var($) to his content
 @param line_until$ -1 because if del VAR$ save spce after and before. Del one
 @param new_expanded_str save the last piece of the string
 @param line_until$_joined
 @param content Comtent of the global var
 @param origin_line_arg the string to advance to obtain line_until$
*/
void	nocontent_runaway(t_aux_pointer *pointer)
{
	pointer->line_until$ = ft_substr(pointer->origin_line_arg, 0, pointer->count_until$ -1);//
	if(pointer->new_expanded_str)
	{
		pointer->line_until$_joined = ft_strjoin(pointer->new_expanded_str, pointer->line_until$);
		new_free(&pointer->new_expanded_str);
	}
	else
		pointer->line_until$_joined = ft_strdup(pointer->line_until$);
	pointer->new_expanded_str = ft_strdup(pointer->line_until$_joined);
	pointer->origin_line_arg = pointer->origin_line_arg + pointer->count_until$ + pointer->size_arg + 1;
	pointer->count_until$ = 0;
	pointer->shell_line_walker+=pointer->size_arg;
}

/* Utiliza shell->command_args que no tiene comando y cambia $ por contenido*/
char *change_dollars(t_shell *shell, char *str_to_change_dollar)
{
	shell->aux_pointer->origin_line_arg = str_to_change_dollar;
	shell->aux_pointer->count_until$ = 0;

	//check_envar(shell);//TODO: seguridad comprobacion variables entorno
	//if (ft_strcmp(shell->line, "exit") == 0)//TODO:Borrar solo para probar leaks aqui
		//shell->exit = 1;
	shell->aux_pointer->shell_line_walker = str_to_change_dollar;
	while (shell->aux_pointer->shell_line_walker && *(shell->aux_pointer->shell_line_walker))
	{
		if (*shell->aux_pointer->shell_line_walker != '$')
		{
			shell->aux_pointer->shell_line_walker++;
			shell->aux_pointer->count_until$++;
		}
		else
			replace_dollar(shell);
	}
	if (str_to_change_dollar&& (int)ft_strlen(str_to_change_dollar) == shell->aux_pointer->count_until$)
		return(str_to_change_dollar);
	if 	(shell->aux_pointer->count_until$)
			shell->aux_pointer->final_str = ft_strjoin(shell->aux_pointer->new_expanded_str, shell->aux_pointer->origin_line_arg );
	else
		shell->aux_pointer->final_str = ft_strdup(shell->aux_pointer->new_expanded_str);
	new_free(&shell->aux_pointer->new_expanded_str);
	return(shell->aux_pointer->final_str);
}

void	replace_dollar(t_shell *shell)
{
	shell->aux_pointer->shell_line_walker++;
	shell->aux_pointer->first_$_found = ft_split_one(shell->aux_pointer->shell_line_walker, ' ', '$');
	shell->aux_pointer->size_arg = ft_strlen(shell->aux_pointer->first_$_found);
	shell->aux_pointer->content= search_var_coincident(shell, shell->aux_pointer->first_$_found);
	if (shell->aux_pointer->content)
		replace_content_runaway(shell->aux_pointer);
	else
		nocontent_runaway(shell->aux_pointer);
	free(shell->aux_pointer->line_until$);
	free(shell->aux_pointer->line_until$_joined);
	free(shell->aux_pointer->first_$_found);
}