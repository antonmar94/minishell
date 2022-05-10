/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_search_dollar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 20:28:58 by albzamor          #+#    #+#             */
/*   Updated: 2022/05/08 19:43:25 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 replace global var(dollar) to his content
 @param line_untildollar substring (malloc) filled with the chars advanceds count_untildollar
 @param new_expanded_str save the last piece of the string
 @param line_untildollar_joined
 @param content Comtent of the global var
 @param origin_line_arg the string to advance to obtain line_untildollar

*/
void replace_content_runaway(t_aux_pointer *pointer)
{
	pointer->line_untildollar = ft_substr(pointer->origin_line_arg, 0, pointer->count_untildollar);
	//si anteriormente ya hay algo se concatena a lo anterior
	if(pointer->new_expanded_str)
	{
		pointer->line_untildollar_joined = ft_strjoin(pointer->new_expanded_str, pointer->line_untildollar);
		new_free(&pointer->new_expanded_str);
	}
	else
		pointer->line_untildollar_joined = ft_strdup(pointer->line_untildollar);
	pointer->new_expanded_str =ft_strjoin(pointer->line_untildollar_joined, pointer->content);
	pointer->origin_line_arg = pointer->origin_line_arg + pointer->count_untildollar + pointer->size_arg + 1;
	pointer->count_untildollar = 0;
	pointer->shell_line_walker+=pointer->size_arg;
	if(pointer->new_expanded_str)
		free(pointer->new_expanded_str);
	pointer->new_expanded_str = ft_strjoin(pointer->line_untildollar_joined, pointer->content);

}

/**
 replace global var(dollar) to his content
 @param line_untildollar -1 because if del VARdollar save spce after and before. Del one
 @param new_expanded_str save the last piece of the string
 @param line_untildollar_joined
 @param content Comtent of the global var
 @param origin_line_arg the string to advance to obtain line_untildollar
*/
void	nocontent_runaway(t_aux_pointer *pointer)
{
	pointer->line_untildollar = ft_substr(pointer->origin_line_arg, 0, pointer->count_untildollar -1);//
	if(pointer->new_expanded_str)
	{
		pointer->line_untildollar_joined = ft_strjoin(pointer->new_expanded_str, pointer->line_untildollar);
		new_free(&pointer->new_expanded_str);
	}
	else
		pointer->line_untildollar_joined = ft_strdup(pointer->line_untildollar);
	pointer->new_expanded_str = ft_strdup(pointer->line_untildollar_joined);
	pointer->origin_line_arg = pointer->origin_line_arg + pointer->count_untildollar + pointer->size_arg + 1;
	pointer->count_untildollar = 0;
	pointer->shell_line_walker+=pointer->size_arg;
}

/* Utiliza shell->command_args que no tiene comando y cambia dollar por contenido*/
char *change_dollars(t_shell *shell, char *str_to_change_dollar)
{
	shell->aux_pointer->origin_line_arg = str_to_change_dollar;
	shell->aux_pointer->count_untildollar = 0;
	shell->aux_pointer->shell_line_walker = str_to_change_dollar;
	while (shell->aux_pointer->shell_line_walker && *(shell->aux_pointer->shell_line_walker))
	{
		if (*shell->aux_pointer->shell_line_walker != '$')
		{
			shell->aux_pointer->shell_line_walker++;
			shell->aux_pointer->count_untildollar++;
		}
		else
			replace_dollar(shell);
	}
	if (str_to_change_dollar&& (int)ft_strlen(str_to_change_dollar) == shell->aux_pointer->count_untildollar)
		return(str_to_change_dollar);
	if 	(shell->aux_pointer->count_untildollar)
			shell->aux_pointer->final_str = ft_strjoin(shell->aux_pointer->new_expanded_str, shell->aux_pointer->origin_line_arg );
	else
		shell->aux_pointer->final_str = ft_strdup(shell->aux_pointer->new_expanded_str);
	new_free(&shell->aux_pointer->new_expanded_str);
	return(shell->aux_pointer->final_str);
}

void	replace_dollar(t_shell *shell)
{
	shell->aux_pointer->shell_line_walker++;
	shell->aux_pointer->first_dollar_found = ft_split_one(shell->aux_pointer->shell_line_walker, ' ', '$');
	//printf("PP fewfwefwefwfeefwfefewfe [%s]\n", shell->aux_pointer->first_dollar_found);
	shell->aux_pointer->size_arg = ft_strlen(shell->aux_pointer->first_dollar_found);
	shell->aux_pointer->content= search_var_coincident(shell, shell->aux_pointer->first_dollar_found);
	if (shell->aux_pointer->content)
		replace_content_runaway(shell->aux_pointer);
	else
		nocontent_runaway(shell->aux_pointer);
	free(shell->aux_pointer->line_untildollar);
	free(shell->aux_pointer->line_untildollar_joined);
	free(shell->aux_pointer->first_dollar_found);
}