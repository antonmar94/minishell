/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1d_search_dollar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 20:28:58 by albzamor          #+#    #+#             */
/*   Updated: 2022/02/28 13:52:42 by albzamor         ###   ########.fr       */
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
	printf("\norigin_line_arg:%s\n" ,pointer->origin_line_arg);//TODO de
	pointer->line_until$ = ft_substr(pointer->origin_line_arg, 0, pointer->count_until$);
	printf("\nline_until$:%s\n" ,pointer->line_until$);//TODO del
	printf("size line_until$: %lu\n", ft_strlen(pointer->line_until$));//TODO del
	//si anteriormente ya hay algo se concatena a lo anterior
	if(pointer->new_expanded_str)
	{
		pointer->line_until$_joined = ft_strjoin(pointer->new_expanded_str, pointer->line_until$);
		new_free(&pointer->new_expanded_str);

	}
	else
		pointer->line_until$_joined = ft_strdup(pointer->line_until$);

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
	{
		pointer->line_until$_joined = ft_strjoin(pointer->new_expanded_str, pointer->line_until$);
		new_free(&pointer->new_expanded_str);
	}
	else
		pointer->line_until$_joined = ft_strdup(pointer->line_until$);

	pointer->new_expanded_str = pointer->line_until$_joined;
	printf("\nunido contenido: pointer->new_expanded_str\n");//TODO del
	printf(GREEN"%s\n"RESET, pointer->new_expanded_str);//TODO del
	printf("size: %lu\n", ft_strlen(pointer->new_expanded_str));
	pointer->origin_line_arg = pointer->origin_line_arg + pointer->count_until$ + pointer->size_arg + 1;
	pointer->count_until$ = 0;
}

/* Utiliza shell->line_args que no tiene comando y cambia $ por contenido*/
char *change_dollars(t_shell *shell, char *str_to_change_dollar)
{

	//shell->aux_pointer = malloc(sizeof(t_aux_pointer));
	shell->aux_pointer->origin_line_arg = str_to_change_dollar;
	shell->aux_pointer->count_until$ = 0;
	//shell->aux_pointer->new_expanded_str = NULL;
	//shell->aux_pointer->final_str = NULL;
	//shell->aux_pointer->new_expanded_str = NULL;
	shell->aux_pointer->first_$_found = NULL;
	//shell->aux_pointer->line_until$_joined = NULL;
	//shell->aux_pointer->content = NULL;
	int i = 0;

	check_envar(shell);//TODO: seguridad comprobacion variables entorno
	printf(RED"%s\n"RESET, str_to_change_dollar);//TODO Del Test

	if (ft_strcmp(shell->line, "exit") == 0)//TODO:Borrar solo para probar leaks aqui
		shell->exit = 1;

	shell->aux_pointer->shell_line_walker = str_to_change_dollar;

	while (shell->aux_pointer->shell_line_walker && *(shell->aux_pointer->shell_line_walker))
	{
		if (*shell->aux_pointer->shell_line_walker != '$')
		{
			shell->aux_pointer->shell_line_walker++;
			shell->aux_pointer->count_until$++;
		}
		else
		{
			shell->aux_pointer->shell_line_walker++;
			shell->aux_pointer->first_$_found = ft_split_one(shell->aux_pointer->shell_line_walker, ' ', '$');
			printf(WHITE"\n %i first$_found: %s\n"RESET, ++i, shell->aux_pointer->first_$_found);
			shell->aux_pointer->size_arg = ft_strlen(shell->aux_pointer->first_$_found);
			printf(CYAN"\nsize first$_found: %d\n"RESET, shell->aux_pointer->size_arg);
			shell->aux_pointer->content= search_var_coincident(shell, shell->aux_pointer->first_$_found);
			printf(CYAN"\ncontent: %s\n"RESET, shell->aux_pointer->content);
			if (shell->aux_pointer->content)
			{
				printf(CYAN"\nExiste Coincidencia shell->aux_pointer->content ✅ \n");
				replace_content_runaway(shell->aux_pointer);
				shell->aux_pointer->shell_line_walker+=shell->aux_pointer->size_arg;
				if(shell->aux_pointer->new_expanded_str)
					free(shell->aux_pointer->new_expanded_str);
				shell->aux_pointer->new_expanded_str = ft_strjoin(shell->aux_pointer->line_until$_joined, shell->aux_pointer->content);
			}
			else
			{
				printf(CYAN"\nNO Existe Coincidencia shell->aux_pointer->content ❌ \n");
				nocontent_runaway(shell->aux_pointer);
				shell->aux_pointer->shell_line_walker+=shell->aux_pointer->size_arg;
				shell->line+=shell->aux_pointer->size_arg +1;
				shell->aux_pointer->new_expanded_str = ft_strdup(shell->aux_pointer->line_until$_joined);
			}
			free(shell->aux_pointer->line_until$);

			printf(RED"\nQUE HAY EXTENDED %s\n"RESET,shell->aux_pointer->new_expanded_str);
			if(shell->aux_pointer->line_until$_joined)
				new_free(&shell->aux_pointer->line_until$_joined);
			if(shell->aux_pointer->first_$_found)
				new_free(&shell->aux_pointer->first_$_found);
			//if((shell->aux_pointer->line_until$))
				//free(shell->aux_pointer->line_until$);
		}
	}
	if (shell->line && (int)ft_strlen(shell->line) == shell->aux_pointer->count_until$)
	{
		return(shell->line);////ARREGLAR AQUIIIIIII
	}

	if 	(shell->aux_pointer->count_until$)
		{
			shell->aux_pointer->final_str = ft_strjoin(shell->aux_pointer->new_expanded_str, shell->aux_pointer->origin_line_arg );
			printf("\nLAST WORDS: %s\n", shell->aux_pointer->origin_line_arg);
			//free(shell->aux_pointer->new_expanded_str);
		}
	else
	{
			free(shell->line);
			shell->line = NULL;

		shell->aux_pointer->final_str = ft_strdup(shell->aux_pointer->new_expanded_str);
		printf("\nLAST WORDS(NADA AL FINAL): %s\n", shell->aux_pointer->origin_line_arg);

	}
	//if(shell->aux_pointer->new_expanded_str)
		//new_free(&shell->aux_pointer->new_expanded_str);

	//if(str_to_change_dollar)
		//free(str_to_change_dollar);// BORRA LEAK LINE!!!
	return(shell->aux_pointer->final_str);
}

