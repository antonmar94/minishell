/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1d_search_dollar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 20:28:58 by albzamor          #+#    #+#             */
/*   Updated: 2022/02/20 01:45:39 by albzamor         ###   ########.fr       */
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
	printf("\norigin_line_arg:%s\n" ,pointer->origin_line_arg);//TODO del
	pointer->line_until$ = ft_substr(pointer->origin_line_arg, 0, pointer->count_until$);
	printf("\nline_until$:%s\n" ,pointer->line_until$);//TODO del
	printf("size line_until$: %lu\n", ft_strlen(pointer->line_until$));//TODO del
	//si anteriormente ya hay algo se concatena a lo anterior
	if(pointer->new_expanded_str)
		pointer->line_until$_joined = ft_strjoin(pointer->new_expanded_str, pointer->line_until$);
	else
		pointer->line_until$_joined = pointer->line_until$;
	pointer->new_expanded_str =ft_strjoin(pointer->line_until$_joined, pointer->content);
	printf("\nunido contenido: pointer->new_expanded_str\n");//TODO del
	printf(GREEN"%s\n"RESET, pointer->new_expanded_str);//TODO del
	printf(CYAN"size: %lu\n", ft_strlen(pointer->new_expanded_str));
	pointer->origin_line_arg = pointer->origin_line_arg + pointer->count_until$ + pointer->size_arg + 1;
	pointer->count_until$ = 0;
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
	printf("\norigin_line_arg:%s\n" ,pointer->origin_line_arg);//TODO del
	pointer->line_until$ = ft_substr(pointer->origin_line_arg, 0, pointer->count_until$ -1);//
	printf("\nline_until$:%s\n" ,pointer->line_until$);//TODO del
	printf("size line_until$: %lu\n", ft_strlen(pointer->line_until$));//TODO del
	if(pointer->new_expanded_str)
		pointer->line_until$_joined = ft_strjoin(pointer->new_expanded_str, pointer->line_until$);
	else
		pointer->line_until$_joined = pointer->line_until$;
	pointer->new_expanded_str = pointer->line_until$_joined;
	printf("\nunido contenido: pointer->new_expanded_str\n");//TODO del
	printf(GREEN"%s\n"RESET, pointer->new_expanded_str);//TODO del
	printf("size: %lu\n", ft_strlen(pointer->new_expanded_str));
	pointer->origin_line_arg = pointer->origin_line_arg + pointer->count_until$ + pointer->size_arg + 1;
	pointer->count_until$ = 0;
}

/* Utiliza shell->line_args que no tiene comando y cambia $ por contenido*/
char *change_dollars(t_shell *shell)
{
	t_aux_pointer *pointer;
	pointer = malloc(sizeof(t_aux_pointer));
	pointer->begin$ = NULL;

	pointer->origin_line_arg = shell->line;
	pointer->last_pos_until$ = 0;
	pointer->count_until$ = 0;
	pointer->new_expanded_str = NULL;

	int i = 0;


	check_envar(shell);//TODO: seguridad comprobacion variables entorno
	printf(YELLOW"fake arguments:\n"RESET);//TODO Del Test
	printf(RED"%s\n"RESET, shell->line);//TODO Del Test
	//printf("fake arguments expanded: ");//TODO Del Test

	pointer->shell_line_walker = shell->line;

	while (pointer->shell_line_walker && *(pointer->shell_line_walker))
	{
		if (*pointer->shell_line_walker != '$')
		{
			pointer->shell_line_walker++;
			pointer->count_until$++;
		}
		else
		{
			pointer->shell_line_walker++;
			pointer->first_$_found = ft_split_one(pointer->shell_line_walker, ' ', '$');
			printf(WHITE"\n %i first$_found: %s\n"RESET, ++i, pointer->first_$_found);
			pointer->size_arg = ft_strlen(pointer->first_$_found);
			printf(CYAN"\nsize first$_found: %d\n"RESET, pointer->size_arg);
			pointer->content= search_var_coincident(shell, pointer->first_$_found);
			printf(CYAN"\ncontent: %s\n"RESET, pointer->content);
			if (pointer->content)
			{
				printf(CYAN"\nExiste Coincidencia pointer->content ✅ \n");
				replace_content_runaway(pointer);
				pointer->shell_line_walker+=pointer->size_arg;
				pointer->new_expanded_str =ft_strjoin(pointer->line_until$_joined, pointer->content);
			}
			else
			{
				printf(CYAN"\nNO Existe Coincidencia pointer->content ❌ \n");
				nocontent_runaway(pointer);
				pointer->shell_line_walker+=pointer->size_arg;
				shell->line+=pointer->size_arg +1;
				pointer->new_expanded_str = pointer->line_until$_joined;
			}
			free_str(pointer->line_until$_joined);
			free_str(pointer->first_$_found);

		}

	}
	if ((int)ft_strlen(shell->line) == pointer->count_until$)
	{
		if (ft_strcmp(shell->line, "exit") == 0)
			shell->exit = 1;
		return(shell->line);
	}
	if 	(pointer->count_until$)
		{
			pointer->final_str = ft_strjoin(pointer->new_expanded_str, pointer->origin_line_arg );
			printf("\nLAST WORDS(NADA AL FINAL): %s\n", pointer->origin_line_arg);

		}
		else
		{
			pointer->final_str = pointer->new_expanded_str;
			printf("\nLAST WORDS(NADA AL FINAL): %s\n", pointer->origin_line_arg);
		}
	return(pointer->final_str);
}

